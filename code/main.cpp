/**
 @file main.cpp
 @brief Giant Sudoku Solver
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 This is a solver for Sudoku problems of any size. Serial, OpenMP, and MPI versions are available. A brutal force solver is implemented in the serial version. For the OpenMP version, we generate n potential boards by an interpolation function and push all the boards into a dequeue.
*/
//  g++ -std=c++11 -fopenmp main.cpp Sudoku.cpp Sudoku_serial.cpp Sudoku_parallel.cpp -o sudoku_run
//  export OMP_NUM_THREADS=8

#include <iostream>
#include <ctime>
#include "Sudoku_serial.hpp"
#include "Sudoku_parallel.hpp"
#include "omp.h"

inline double wtime() {return omp_get_wtime();}

int main(int argc, const char * argv[]) {
    int len = 16;
    std::string filename ="../test_cases/test16_2.sdk";
    // Serial Version
    clock_t begin = clock();
    SudokuSerial ss(filename, len);
    ss.solve();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << " seconds.\n";
    // OpenMP Version
    double wbegin = wtime();
    SudokuParallel sp(filename, len);
    sp.solve();
    double wend = wtime();
    double welapsed_secs = wend - wbegin;
    std::cout << welapsed_secs << " seconds, by omp wtime.\n";
    return 0;
}
