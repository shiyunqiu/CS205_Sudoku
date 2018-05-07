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

    Sudoku::BSIZE      = (argc > 1) ? atoi(argv[1]) : 16;
    Sudoku::IFILE_NAME = (argc > 2) ? argv[2] : "../test_cases/test16_1min.sdk";
    Sudoku::OFILE_NAME = (argc > 3) ? argv[3] : "./solutions.txt";

    int mode = (argc > 4) ? atoi(argv[4]) : 0;

    if (mode <= 0) {
        // Serial Mode
        SudokuSerial sudoku(argc, argv);
        sudoku.run();
    } else if (mode == 1) {
        // OMP Mode
        SudokuQueueScheme::BOOTSTRAP_NUM = (argc > 5) ? atoi(argv[5]) : 512;
        SudokuQueueScheme sudoku(argc, argv);
        sudoku.run();
    } else if (mode >= 2) {
        // MPI Mode
        SudokuMPI::BOOTSTRAP_NUM_1 = (argc > 5) ? atoi(argv[5]) : 512;
        SudokuMPI::BOOTSTRAP_NUM_2 = (argc > 6) ? atoi(argv[6]) : 512;
        SudokuMPI::SHUFFLE         = (argc > 7) ? atoi(argv[7]) : 0; // whether to shuffle the task queue before assigning to each node 
        SudokuMPI::SHUFFLE_SEED    = (argc > 8) ? atoi(argv[8]) : 0;
        if (mode == 2) {
            // MPI Static Scheduling
            SudokuMPIStatic sudoku(argc, argv);
            sudoku.run();
        } else {
            // MPI Dynamic Scheduling
            SudokuMPIDynamic sudoku(argc, argv);
            sudoku.run();
        }
    }

    return 0;
}