/**
 @file sudoku_mpi_static.hpp
 @brief Header file for the static scheduled MPI version of the Sudoku solver.
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 */

#ifndef SUDOKU_MPI_DYNAMIC_H
#define SUDOKU_MPI_DYNAMIC_H

#include <iostream>
#include "board_deque.hpp"
#include "bootstrapper.hpp"
#include "sudoku_mpi.hpp"


class SudokuMPIDynamic: public SudokuMPI {

public:
    SudokuMPIDynamic(int argc, char** argv): SudokuMPI(argc, argv) {
        if (mpi_size < 2) {
            std::cerr << "Error: need at least 2 processors to perform dynamic scheduling" << std::endl;
            exit(1);
        }
        if (mpi_rank == 0) {
            mpi_reqvac_master = new MPI_Request[mpi_size-1];
        }
    }
    ~SudokuMPIDynamic() {
        if (mpi_rank == 0) {
            delete [] mpi_reqvac_master;
        }
    }
    virtual void task_process();

protected:
    void single_proc_solve(Bootstrapper& probs, BoardDeque& sols);

protected:
    MPI_Request mpi_reqover;
    MPI_Request mpi_reqvac_slave;
    MPI_Request* mpi_reqvac_master;

protected:
    static const int SMPI_TAGOVER = 1;
    static const int SMPI_TAGVAC = 2;
    static const int SMPI_TAGRES = 3;
};

#endif