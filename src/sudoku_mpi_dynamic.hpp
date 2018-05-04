/**
 @file sudoku_mpi_dynamic.hpp
 @brief Header file for the MPI dynamic scheduling version of the Sudoku solver.
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 1, 2018
 */

#ifndef SUDOKU_MPI_DYNAMIC_H
#define SUDOKU_MPI_DYNAMIC_H

#include <iostream>
#include "board_deque.hpp"
#include "bootstrapper.hpp"
#include "sudoku_mpi.hpp"

/**
 @class SudokuMPIDynamic
 @brief Derived class of SudokuMPI, dynamic scheduling. Master node is constantly querying about the status of the slave nodes, and will assign new jobs to the slave node if it finishes all previously assigned work.
 
 This is an inherited class of the SudokuMPI class. It has one constructor, one destructor, one public method, one protected method, and four protected variables.
 */
class SudokuMPIDynamic: public SudokuMPI {

public:
    /** Constructor of class SudokuMPIDynamic: ensure at least 2 processors exist and initialize the MPI_Request
     @param argc [argument count]
     @param argv [argument vector]
    */
    SudokuMPIDynamic(int argc, char** argv): SudokuMPI(argc, argv) {
        if (mpi_size < 2) {
            std::cerr << "Error: need at least 2 processors to perform dynamic scheduling" << std::endl;
            exit(1);
        }
        // slave nodes should be number of processors minus 1
        if (mpi_rank == 0) {
            mpi_reqvac_master = new MPI_Request[mpi_size-1];
        }
    }

    /** Destructor of class SudokuMPIDynamic: clean up the MPI process. */
    ~SudokuMPIDynamic() {
        if (mpi_rank == 0) {
            delete [] mpi_reqvac_master;
        }
    }
    virtual void task_process();

protected:
    void single_proc_solve(Bootstrapper& probs, BoardDeque& sols);

    MPI_Request mpi_reqvac_slave;
    MPI_Request* mpi_reqvac_master;

    static const int SMPI_TAGOVER = 1;
    static const int SMPI_TAGVAC = 2;
};

#endif