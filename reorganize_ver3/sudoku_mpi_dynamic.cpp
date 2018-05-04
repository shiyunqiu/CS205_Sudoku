/**
 @file sudoku_mpi.cpp
 @brief Implementation for the MPI version of the Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 
 Generate potential boards of solutions by bootstrapping, and assign jobs to each thread in each node. Solve the Sudoku puzzle simultaneously by all nodes using MPI.
 */
#include <iostream>
#include <sstream>
#include <vector>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku_mpi_dynamic.hpp"


/* Solve the problem in parallel using MPI combined with OpenMP. */
void SudokuMPIDynamic::task_process() {

    Bootstrapper probs;
    std::stringstream message;

    /* task preparation */
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
    }


    /* dynamicly scheduled processing */
    if (mpi_rank == 0) {

        int r = 1;
        int N = probs.size();

        // set up receivers for vacancy notes
        for (r = 1; r < mpi_size; r++) {
            MPI_Irecv(NULL, 0, MPI_INT, 
                      r, SMPI_TAGVAC, 
                      MPI_COMM_WORLD, 
                      &mpi_reqvac_master[r-1]);
        }

        // assign tasks
        r = 1;
        int is_vac;
        while (probs.size() > 0) {
            is_vac = 0;
            MPI_Test(&mpi_reqvac_master[r-1],
                     &is_vac,
                     &mpi_status);
            if (is_vac) {
                std::cout << "\rRANK-" << mpi_rank << ": "; 
                std::cout << "task queue assigning" << "...";
                std::cout << N-probs.size()+1 << "/" << N << std::flush;
                SMPI_DumpDeque(probs, r, 1); // this sends 1 board
                MPI_Irecv(NULL, 0, MPI_INT, 
                          r, SMPI_TAGVAC, 
                          MPI_COMM_WORLD, 
                          &mpi_reqvac_master[r-1]);
            }
            r = r % (mpi_size-1) + 1;
        }
        std::cout << ", exhausted" << std::endl;

        // send out task-over message (empty assignment)
        for (int n_active = mpi_size-1; n_active > 0; n_active--) {
            MPI_Waitany(mpi_size-1, 
                        mpi_reqvac_master, 
                        &r, &mpi_status);
            SMPI_DumpDeque(probs, r+1, 0); // this sends NO board
        }
    }
    else {

        int count = 0;
        while (true) {

            // send out vacancy note
            MPI_Isend(NULL, 0, MPI_INT, 
                      0, SMPI_TAGVAC, 
                      MPI_COMM_WORLD, 
                      &mpi_reqvac_slave);
            MPI_Wait(&mpi_reqvac_slave, 
                     &mpi_status);

            // get response from the master
            int n_assign = SMPI_LoadDeque(probs, 0);

            // process
            if (n_assign > 0) {
                // which is a valid assignment
                single_proc_solve(probs, sols); // also clears up probs
                count += n_assign;
            } else {
                // which is interpreted as a task-over message
                message.str(std::string());
                message << "RANK-" << mpi_rank << ": ";
                message << sols.size() << " solutions found" << ", ";
                message << "in " << count << " assignments" << std::endl;
                std::cout << message.str();
                break;
            }
        }
    }

    /* result collection */
    if (mpi_rank != 0){
        SMPI_DumpDeque(sols, 0, -1);
    }
    else {
        for (int r = 1; r < mpi_size; r++){
            SMPI_LoadDeque(sols, r);
        }
        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "results collected" << std::endl;
    }
}


void SudokuMPIDynamic::single_proc_solve(Bootstrapper& probs, BoardDeque& sols) {

    while (probs.size() > 0 && 
            probs.size() < BOOTSTRAP_NUM_2) {
        probs.bootstrap();
    }
    probs.solutions().dump(sols);

    int N = probs.size();
    std::vector<Solver> solvers(N);

    for (int i = 0; i < N; i++) {
        probs.pass(solvers[i]);
    }

    #pragma omp parallel for \
            schedule(dynamic) \
            shared(N, solvers)
    for (int i = 0; i < N; i++) {
        solvers[i].solve();
    }

    for (int i = 0; i < N; i++) {
        solvers[i].dump(sols);
    }
}





