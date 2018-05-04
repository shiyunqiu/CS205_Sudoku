/**
 @file sudoku_mpi_static.hpp
 @brief Header file for the MPI static scheduling version of the Sudoku solver.
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 */

#ifndef SUDOKU_MPI_STATIC_H
#define SUDOKU_MPI_STATIC_H

#include "sudoku_mpi.hpp"

/**
 @class SudokuMPIStatic
 @brief Derived class of SudokuMPI, static scheduling. Each node is assigned certain amount of work in the beginning.
 
 This is an inherited class of the SudokuMPI class. It has one constructors and one public method.
 */
class SudokuMPIStatic: public SudokuMPI {

public:
    SudokuMPIStatic(int argc, char** argv): SudokuMPI(argc, argv) {}
    virtual void task_process();
};

#endif