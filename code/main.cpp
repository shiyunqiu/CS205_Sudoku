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
    std::string filename ="/Users/shell/Documents/Projects/cs205_final/test_cases/test16_2.sdk";
    clock_t begin = clock();
    SudokuParallel sp(filename, len);
    sp.solve();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << " seconds.\n";
    return 0;
}
