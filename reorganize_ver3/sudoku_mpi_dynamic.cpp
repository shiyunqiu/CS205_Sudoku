/**
 @file sudoku_mpi.cpp
 @brief Implementation for the MPI version of the Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 
 Generate potential boards of solutions by bootstrapping, and assign jobs to each thread in each node. Solve the Sudoku puzzle simultaneously by all nodes using MPI.
 */
#include <iostream>
#include <vector>
#include <deque>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku_mpi_dynamic.hpp"


/* Solve the problem in parallel using MPI combined with OpenMP. */
void SudokuMPIDynamic::task_process() {

    Bootstrapper probs;

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


    /* dynamic scheduled processing */
    if (mpi_rank == 0) {

        int N = probs.size();

        while (probs.size() > 0) {

            std::cout << "\rRANK-" << mpi_rank << ": "; 
            std::cout << "task queue assigning" << "...";
            std::cout << N-probs.size()+1 << "/" << N << std::flush;

            int rvac = SMPI_SeekVacancy();
            SMPI_DumpDeque(probs, rvac, 1);
        }

        std::cout << ", exhausted" << std::endl;

        for (int r = 1; r < mpi_size; r++) {
            MPI_Isend(NULL, 0, MPI_INT, 
                      r, SMPI_TAGOVER, 
                      MPI_COMM_WORLD, 
                      &mpi_reqover);
            MPI_Wait(&mpi_reqover, 
                     &mpi_status);
        }
    }
    else {

        MPI_Irecv(NULL, 0, MPI_INT, 
                  0, SMPI_TAGOVER, 
                  MPI_COMM_WORLD, 
                  &mpi_reqover);

        int count = 0;

        while (true) {

            int is_over = 0;
            MPI_Test(&mpi_reqover, 
                     &is_over, 
                     &mpi_status);
            if (is_over) {
                std::cout << "RANK-" << mpi_rank << ": "; 
                std::cout << sols.size() << " solutions found" << ", ";
                std::cout << "in " << count << " attemps" << std::endl;
                break;
            }

            SMPI_PostVacancy();
            SMPI_LoadDeque(probs, 0);
            count++;

            single_proc_solve(probs, sols); // also clears up probs
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


void SudokuMPIDynamic::SMPI_PostVacancy(int mpi_tag) {

    MPI_Isend(NULL, 0, MPI_INT, 
              0, mpi_tag, 
              MPI_COMM_WORLD, 
              &mpi_reqvac_slave);

    MPI_Wait(&mpi_reqvac_slave, 
             &mpi_status);
}


int SudokuMPIDynamic::SMPI_SeekVacancy(int mpi_tag) {

    for (int r = 1; r < mpi_size; r++) {
        MPI_Irecv(NULL, 0, MPI_INT, 
                  r, mpi_tag, 
                  MPI_COMM_WORLD, 
                  mpi_reqvac_master+r-1);
    }

    int rvac;
    MPI_Waitany(mpi_size-1, 
                mpi_reqvac_master, 
                &rvac, &mpi_status);

    return ++rvac;
}





