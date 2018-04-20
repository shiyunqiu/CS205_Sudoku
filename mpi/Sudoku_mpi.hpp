//
//  Sudoku_parallel.hpp
//  Sudoku
//
//  Created by Yiqi Xie on 4/19/18.
//  Copyright © 2018 Yiqi Xie. All rights reserved.
//

#ifndef SUDOKU_MPI_HPP
#define SUDOKU_MPI_HPP

#include "Sudoku.hpp"
#include "Sudoku_serial.hpp"
#include "Sudoku_parallel.hpp"
#include <deque>

/** A parallel Sudoku solver. */
class SudokuMPI : public SudokuParallel {
public:
    SudokuMPI() : SudokuParallel() {}
    SudokuMPI(const std::vector<std::vector<int> >& board, int& grid_size) : SudokuParallel(board, grid_size) { analyze(); }
    SudokuMPI(const std::string& filename, int& grid_size) : SudokuParallel(filename, grid_size) { analyze(); }
    SudokuMPI(const int* array, int& grid_size) : SudokuParallel(array, grid_size) { analyze(); }
    void solve(bool warm_start=false);
    virtual void analyze();
    static int SMNGEN; // default number for ngen (making tests easier)
private:
    // Number of generations of bootstrapping to perform.
    // note Optimal value determined experimentally. 
    int ngen;
};

#endif
