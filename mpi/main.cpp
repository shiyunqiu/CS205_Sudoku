//
//  main.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "Sudoku_serial.hpp"
#include "Sudoku_parallel.hpp"
#include "Sudoku_mpi.hpp"
// #include <omp.h>


int main(int argc, char * argv[]) {

    int gridsize = 16;
    std::string filename ="/Users/shell/Documents/Projects/cs205_final/test_cases/test16_2.sdk";
    // omp_set_num_threads(2);
    SudokuParallel::SPNGEN = 2; // default ngen for SudokuParallel. 
    SudokuMPI::SMNGEN = 4;      // default ngen for SudokuMPI.
    // NOTE: setting SPNGEN / SMNGEN to 0 (or anything < 1) awakes the "magic function" written by Chris
    SudokuMPI sudoku_mpi(filename, gridsize);
    sudoku_mpi.solve();
    return 0;
}
