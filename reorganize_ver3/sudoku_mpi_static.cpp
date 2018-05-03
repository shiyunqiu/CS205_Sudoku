/**
 @file sudoku_mpi.cpp
 @brief Implementation for the MPI version of the Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 
 Generate potential boards of solutions by bootstrapping, and assign jobs to each thread in each node. Solve the Sudoku puzzle simultaneously by all nodes using MPI.
 */
// #include <iostream>
#include <vector>
#include <deque>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku_mpi_static.hpp"

/* Solve the problem in parallel using MPI combined with OpenMP. */
void SudokuMPIStatic::task_process() {

    Bootstrapper probs;

    /* task assignment */
    if (mpi_rank == 0) {

        // bootstrapping
        probs.push_back(board);
        while (probs.size() > 0 && 
                probs.size() < BOOTSTRAP_NUM_1) {
            probs.bootstrap();
        }
        probs.solutions().dump(sols);

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "task queue of " << probs.size() << " boards bootstrapped" << std::endl;

        if (SHUFFLE) {
            probs.shuffle(SHUFFLE_SEED);
            std::cout << "RANK-" << mpi_rank << ": "; 
            std::cout << "task queue shuffled" << std::endl;
        }
        
        // separate into mpi_size chunks, nper per chunk except for the last chunk
        std::deque<int> schedule;
        int n = probs.size();
        int nper = n / mpi_size;
        while (n >= 2 * nper) {
            schedule.push_back(nper); 
            n -= nper;
        }
        schedule.push_back(n); // the largest chunk is at the back of it
        
        // assign the boards to each node
        int nloc;
        for (int r = 1; r < mpi_size; r++) {
            nloc = schedule.back();
            SMPI_DumpDeque(probs, r, nloc);
            schedule.pop_back();
        }

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << probs.size() << " boards kept" << std::endl;
    }
    else {
        
        SMPI_LoadDeque(probs, 0);

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << probs.size() << " boards assigned" << std::endl;
    }

    /* parallel processing */

    // boostrapping to make sure that each thread in each node get assigned a job
    while (probs.size() > 0 && 
            probs.size() < BOOTSTRAP_NUM_2) {
        probs.bootstrap();
    }
    probs.solutions().dump(sols);

    std::cout << "RANK-" << mpi_rank << ": ";
    std::cout << "sub queue augmented to " << probs.size() << " boards" << std::endl; 
    
    int N = probs.size();
    std::vector<Solver> solvers(N);
    
    #pragma omp parallel for \
            schedule(dynamic) \
            shared(N, probs, solvers)
    for (int i = 0; i < N; i++) {
        solvers[i].solve(probs[i]);
    }

    for (int i = 0; i < N; i++) {
        solvers[i].dump(sols);
    }

    std::cout << "RANK-" << mpi_rank << ": "; 
    std::cout << sols.size() << " solutions found" << std::endl;

    /* result collection */

    if (mpi_rank == 0){

        for (int r = 1; r < mpi_size; r++){
            SMPI_LoadDeque(sols, r);
        }

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "results collected" << std::endl;
    }
    else {

        SMPI_DumpDeque(sols, 0, -1);
    }
}