//
//  Sudoku_parallel.hpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/18/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#ifndef SUDOKU_PARALLEL_HPP
#define SUDOKU_PARALLEL_HPP

#include "Sudoku.hpp"
#include "Sudoku_serial.hpp"
#include <deque>

/** A parallel Sudoku solver. */
class SudokuParallel : public Sudoku {
public:
    SudokuParallel() : Sudoku() {}
    SudokuParallel(const std::vector<std::vector<int> >& board, int& grid_size) : Sudoku(board, grid_size) { analyze(); }
    SudokuParallel(const std::string& filename, int& grid_size) : Sudoku(filename, grid_size) { analyze(); }
    SudokuParallel(const Sudoku& s) : Sudoku(s) { analyze(); } // deep copy
    SudokuParallel(const int* array, int& grid_size) : Sudoku(array, grid_size) { analyze(); }
    void solve(bool warm_start=false);
    virtual void analyze();
    void generate();
    /** Sequence of boards used to bootstrap parallelization. */
    std::deque<SudokuSerial> starts;
    std::deque<Sudoku> solutions;
    /** Number of generations of bootstrapping to perform.
     * \note Optimal value determined experimentally. */
    static int SPNGEN; // default number for ngen (making tests easier)
private:
    int ngen; // has to be private (or at least protected?) so that it won't be overridden by SudokuMPI.ngen
};

#endif
