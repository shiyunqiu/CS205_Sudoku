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
    virtual void solve(int row=0, int col=0);
protected:
    void analyze();
    void generate();
    /** Number of generations of bootstrapping to perform.
     * \note Optimal value determined experimentally. */
    int ngen;
    /** Sequence of boards used to bootstrap parallelization. */
    std::deque<SudokuSerial> starts;
};

#endif
