/**
 @file sudoku_mpi.h
 @author Yiqi Xie
 @date April 21, 2018
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


class SudokuMPI {

public:
    SudokuMPI(int bsize, int* argc=NULL, char*** argv=NULL): 
    bsize(bsize), probs(), sols(), schedule() {
        MPI_Init(argc, argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
        if (mpi_rank == 0) {
            std::cout << "Sudoku MPI started with " << mpi_size << " processes" << std::endl << std::endl;
        }
    }
    ~SudokuMPI() {
        MPI_Finalize();
        if (mpi_rank == 0) {
            std::cout << "Sudoku MPI terminated" << std::endl;
        }
    }
    void task_begin(const std::string& filename);
    void task_assign();
    void task_process();
    void task_collect();
    void task_end(std::ostream& out=std::cout);

public:
    static int BOOTSTRAP_N1;
    static int BOOTSTRAP_N2;

protected:
    void SMPI_DumpDeque(BoardDeque& bdeque, int r, int len=-1);
    void SMPI_LoadDeque(BoardDeque& bdeque, int r);
    void SMPI_SendBoard(Board& b, int r);
    void SMPI_RecvBoard(Board& b, int r);

protected:
    int mpi_rank;
    int mpi_size;
    MPI_Status mpi_state;

    int bsize;
    Bootstrapper probs; 
    BoardDeque sols;
    std::deque<int> schedule;

    double t_start;
    double t_end;
};

#endif