//
//  Sudoku_serial.h
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#ifndef SUDOKU_SERIAL_HPP
#define SUDOKU_SERIAL_HPP

#include "Sudoku.hpp"


/** A serial Sudoku solver. */
class SudokuSerial:public Sudoku {
public:
    SudokuSerial() : Sudoku() {}
    SudokuSerial(const std::vector<std::vector<int> >& board, int& grid_size) : Sudoku(board, grid_size) {}
    SudokuSerial(const std::string& filename, int& grid_size) : Sudoku(filename, grid_size) {}
    SudokuSerial(const Sudoku& s) : Sudoku(s) {} // deepcopy
    virtual void solve(int row=0, int col=0);
    void print();
    friend class SudokuParallel;
};

#endif
