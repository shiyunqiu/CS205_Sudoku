/**
 @file sudoku_mpi.cpp
 @brief Implementation for the MPI version of the Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Generate potential boards of solutions by bootstrapping, and assign jobs to each thread in each node. Solve the Sudoku puzzle simultaneously by all nodes using MPI.
 */
#include <iostream>
#include <deque>
#include <vector>
#include <mpi.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku.hpp"
#include "sudoku_mpi.hpp"


// seed for the shuffling the first bootstrapping result
unsigned SudokuMPI::SEED = std::chrono::system_clock::now().time_since_epoch().count();
// number of bootstrapping needed to assign jobs to each node
int SudokuMPI::BOOTSTRAP_NUM_1 = 8;
// number of bootstrapping needed to assign jobs to each thread
int SudokuMPI::BOOTSTRAP_NUM_2 = 16;

/* Read the content of a puzzle file, push the problem to a deque, and output the board. */
void SudokuMPI::task_begin() {

    // if (mpi_rank == 0) {

    //     Board board(BSIZE);
    //     read(board); 
    //     probs.push_back(board);

    //     std::cout << "Problem Board" << std::endl;
    //     board.output(std::cout);
    // }
}


/* Bootstrapping: generate n (determined by BOOTSTRAP_NUM_1 and the bootstrap function) potential boards and push them into a deque to be solved in parallel. Divide the problem into several chunks according to the number of nodes available, separate the deque and assign smaller deques to each node. */
void SudokuMPI::task_assign() {

    // if (mpi_rank == 0) {
    //     // bootstrapping
    //     while (probs.size() > 0 && 
    //             probs.size() < BOOTSTRAP_NUM_1) {
    //         probs.bootstrap();
    //     }
    //     probs.solutions().dump(sols);

    //     std::cout << "RANK-" << mpi_rank << ": "; 
    //     std::cout << "task queue of " << probs.size() << " boards bootstrapped" << std::endl;
    //     // separate into mpi_size chunks, nper per chunk except for the last chunk
    //     int n = probs.size();
    //     int nper = n / mpi_size;
    //     while (n >= 2 * nper) {
    //         schedule.push_back(nper); 
    //         n -= nper;
    //     }
    //     schedule.push_back(n); // the largest chunk is at the back of it
    //     // assign the boards to each node
    //     int nloc;
    //     for (int r = 1; r < mpi_size; r++) {
    //         nloc = schedule.back();
    //         SMPI_DumpDeque(probs, r, nloc);
    //         schedule.pop_back();
    //     }

    //     std::cout << "RANK-" << mpi_rank << ": "; 
    //     std::cout << probs.size() << " boards kept" << std::endl;
    // }
    // else {

    //     SMPI_LoadDeque(probs, 0);

    //     std::cout << "RANK-" << mpi_rank << ": "; 
    //     std::cout << probs.size() << " boards assigned" << std::endl;
    // }
}

/* Solve the problem in parallel using MPI combined with OpenMP. */
void SudokuMPI::task_process() {

    Bootstrapper probs;

    if (mpi_rank == 0) {

        Board board(BSIZE);
        read(board); 
        probs.push_back(board);

        std::cout << "Problem Board" << std::endl;
        board.output(std::cout);
    }
    

    if (mpi_rank == 0) {
        // bootstrapping
        while (probs.size() > 0 && 
                probs.size() < BOOTSTRAP_NUM_1) {
            probs.bootstrap();
        }
        probs.solutions().dump(sols);
        probs.shuffle(SEED);

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "task queue of " << probs.size() << " boards bootstrapped" << std::endl;
        
        // separate into mpi_size chunks, nper per chunk except for the last chunk
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
}

/* Collect the solutions found by all threads and all nodes. */
void SudokuMPI::task_collect() {

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

/* Write the solutions into a file, and print out the solution boards. */
void SudokuMPI::task_end() {

    if (mpi_rank == 0) {

        write(sols);
        std::cout << "Solution Board(s)" << std::endl;
        sols.output(std::cout);    
    }
}

/* Start of the MPI timer. */
void SudokuMPI::timer_start() {
    t_start = MPI_Wtime();
}

/* End of the MPI timer and show elapsed time of execution. */
void SudokuMPI::timer_stop() {
    t_stop = MPI_Wtime();
    if (mpi_rank == 0) {
        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "Elapsed in " << t_stop - t_start << " ";
        std::cout << "seconds (MPI)" << std::endl << std::endl;
    }
}

/** Send boards to a node
 @param bdeque [a deque of board]
 @param r [destination]
 @param len [number of boards to be sent to a node]
 */
void SudokuMPI::SMPI_DumpDeque(BoardDeque& bdeque, int r, int len) {

    if (len < 0) {
        len = bdeque.size();
    }

    MPI_Send(&len, 1, MPI_INT, 
             r, 50, MPI_COMM_WORLD);

    for (int i = 0; i < len; i++) {
        Board& b = bdeque.front();
        SMPI_SendBoard(b, r);
        bdeque.pop_front();
    }
}

/** Receive boards from a node
 @param bdeque [a deque of board]
 @param r [source]
 */
void SudokuMPI::SMPI_LoadDeque(BoardDeque& bdeque, int r) {
    //number of boards
    int len;
    MPI_Recv(&len, 1, MPI_INT, 
             r, 50, MPI_COMM_WORLD, &mpi_state);

    for (int i = 0; i < len; i++) {
        Board b(BSIZE);
        SMPI_RecvBoard(b, r);
        bdeque.push_back(b);
    }
}

/** Send a board
 @param b [board]
 @param r [destination]
 */
void SudokuMPI::SMPI_SendBoard(Board& b, int r) {

    MPI_Send(b.as_array(), 
             BSIZE * BSIZE, MPI_INT, 
             r, 50, MPI_COMM_WORLD);
}

/** Receive a board
 @param b [board]
 @param r [source]
 */
void SudokuMPI::SMPI_RecvBoard(Board& b, int r) {

    MPI_Recv(b.as_array(), 
             BSIZE * BSIZE, MPI_INT, 
             r, 50, MPI_COMM_WORLD, &mpi_state);
}


