/**
 @file sudoku_mpi_static.hpp
 @brief Header file for the static scheduled MPI version of the Sudoku solver.
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 */

#ifndef SUDOKU_MPI_STATIC_H
#define SUDOKU_MPI_STATIC_H

#include "sudoku_mpi.hpp"

class SudokuMPIStatic: public SudokuMPI {

public:
    SudokuMPIStatic(int argc, char** argv): SudokuMPI(argc, argv) {}
    virtual void task_process();
};

#endif