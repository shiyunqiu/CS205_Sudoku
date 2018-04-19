//
//  main.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <iostream>
#include <ctime>
// #include "Sudoku_serial.hpp"
#include "Sudoku_parallel.hpp"
#include "omp.h"

inline double wtime() {return omp_get_wtime();}

int main(int argc, const char * argv[]) {
    // int len = 16;
    // std::string filename ="/Users/shell/Documents/Projects/cs205_final/test_cases/test16_2.sdk";
    // clock_t begin = clock();
    // SudokuSerial ss(filename, len);
    // ss.solve();
    // clock_t end = clock();
    // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    // std::cout << elapsed_secs << " seconds.\n";
    int len = 16;
    omp_set_num_threads(2);
    std::string filename ="/Users/shell/Documents/Projects/cs205_final/test_cases/test16_2.sdk";
    clock_t begin = clock();
    double wbegin = wtime();
    SudokuParallel sp(filename, len);
    sp.solve();
    double wend = wtime();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    double welapsed_secs = wend - wbegin;
    std::cout << elapsed_secs << " seconds, by clock.\n";
    std::cout << welapsed_secs << " seconds, by omp wtime.\n";
    return 0;
}
