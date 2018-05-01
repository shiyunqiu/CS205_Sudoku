/**
 @file sudoku_mpi.cpp
 @brief Implementation for the MPI version of the Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Generate potential boards of solutions by bootstrapping, and assign jobs to each thread in each node. Solve the Sudoku puzzle simultaneously by all nodes using MPI.
 */
#include <iostream>
#include <mpi.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "sudoku.hpp"
#include "sudoku_mpi.hpp"


// configurations for shuffling the first bootstrapping result
bool SudokuMPI::SHUFFLE = false;
unsigned SudokuMPI::SHUFFLE_SEED = std::chrono::system_clock::now().time_since_epoch().count();
// number of bootstrapping needed to assign jobs to each node
int SudokuMPI::BOOTSTRAP_NUM_1 = 8;
// number of bootstrapping needed to assign jobs to each thread
int SudokuMPI::BOOTSTRAP_NUM_2 = 16;

/* Read the content of a puzzle file, push the problem to a deque, and output the board. */
void SudokuMPI::task_begin() {

    if (mpi_rank == 0) {

        read(board); 

        std::cout << "Problem Board" << std::endl;
        board.output(std::cout);
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
        std::cout << "seconds (MPI WALL)" << std::endl << std::endl;
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


