/**
 @file main.cpp
 @brief Giant Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 This is a solver for Sudoku problems of any size. Serial, OpenMP, and MPI+OpenMP versions are available. A brutal force solver is implemented in the serial version. For the parallel version, we generate n potential boards by bootstrapping and push all the boards into a dequeue. OpenMP enables all threads to solve the Sudoku puzzle simultaneously while MPI makes sure that all nodes are solveing the problem in parallel.
 */

#include "sudoku_serial.hpp"
#include "sudoku_queue_scheme.hpp"
#include "sudoku_mpi_static.hpp"
#include "sudoku_mpi_dynamic.hpp"


int main(int argc, char** argv) {

    // Please check input file path and output file path before running

    // Change problem size, input and output path
    Sudoku::BSIZE = 16;
    Sudoku::IFILE_NAME = "../test_cases/test16_5min.sdk";
    Sudoku::OFILE_NAME = "./solutions.txt";

    // Uncomment the line below for serial solver
    SudokuSerial sudoku(argc, argv); 

    // Uncomment three lines below for OpenMP version
    // SudokuQueueScheme::THREAD_NUM = 2;
    // SudokuQueueScheme::BOOTSTRAP_NUM = 512;
    // SudokuQueueScheme sudoku(argc, argv);

    // Uncomment four lines below for MPI+OpenMP version
    // SudokuMPI::SHUFFLE = false; // whether to shuffle the task queue before assigning to each node 
    // SudokuMPI::SHUFFLE_SEED = 9001;
    // SudokuMPI::BOOTSTRAP_NUM_1 = 512;
    // SudokuMPI::BOOTSTRAP_NUM_2 = 2048;

    // MPI Static scheduling
    // SudokuMPIStatic sudoku(argc, argv);

    // MPI Dynamic scheduling
    // SudokuMPIDynamic sudoku(argc, argv);

    sudoku.run();

    return 0;
}