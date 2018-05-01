/**
 @file sudoku_mpi.hpp
 @brief Header file for the MPI version of the Sudoku solver.
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SUDOKU_MPI_H
#define SUDOKU_MPI_H

#include <iostream>
#include <deque>
#include <mpi.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku.hpp"

/**
 @class SudokuMPI
 @brief Derived class of Sudoku, solve the Sudoku puzzle in parallel with MPI.
 
 This is an inherited class of the Sudoku class. It has one constructor, one destructor, seven public methods, two public variables, four protected methods and eight protected variables.
 */
class SudokuMPI: public Sudoku {

public:
    /** Constructor of classSudokuMPI: initialize MPI and set up MPI communicators, print out the number of processes
     @param argc [argument count]
     @param argv [argument vector]
     */
    SudokuMPI(int argc, char** argv) {
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
        if (mpi_rank == 0) {
            std::cout << "Sudoku MPI started with " << mpi_size << " processes" << std::endl << std::endl;
        }
    }
    
    /* Destructor of classSudokuMPI: clean up the MPI process. */
    ~SudokuMPI() {
        MPI_Finalize();
        if (mpi_rank == 0) {
            std::cout << "Sudoku MPI terminated" << std::endl;
        }
    }
    virtual void task_begin();
    virtual void task_assign();
    virtual void task_process();
    virtual void task_collect();
    virtual void task_end();
    virtual void timer_start();
    virtual void timer_stop();

public:
    static unsigned SEED;
    static int BOOTSTRAP_NUM_1;
    static int BOOTSTRAP_NUM_2;

protected:
    void SMPI_DumpDeque(BoardDeque& bdeque, int r, int len=-1);
    void SMPI_LoadDeque(BoardDeque& bdeque, int r);
    void SMPI_SendBoard(Board& b, int r);
    void SMPI_RecvBoard(Board& b, int r);

protected:
    int mpi_rank;
    int mpi_size;
    MPI_Status mpi_state;

    // Bootstrapper probs; 
    BoardDeque sols;
    std::deque<int> schedule;

    double t_start;
    double t_stop;
};

#endif
