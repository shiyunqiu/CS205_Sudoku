/**
 @file Sudoku_serial.hpp
 @brief Header file for the serial class
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SUDOKU_SERIAL_HPP
#define SUDOKU_SERIAL_HPP

#include "Sudoku.hpp"

/**
 @class SudokuSerial
 @brief Derived class of Sudoku, serial version of the Sudoku Solver
 
 This is an inherited class of the Sudoku class. It has three constructors, one copy constructor, and two public functions. It inherits two functions and two variables from the base class.
 */
class SudokuSerial:public Sudoku {
public:
    SudokuSerial() : Sudoku() {}
    /** constructor of class SudokuSerial: save the Sudoku puzzle and the grid size of the puzzle board
     @param board [Sudoku puzzle board]
     @param grid_size [Size (column length) of Sudoku puzzle board]
     */
    SudokuSerial(const std::vector<std::vector<int> >& board, int& grid_size) : Sudoku(board, grid_size) {}
    /** constructor of class SudokuSerial: read Sudoku puzzle problem from a sdk file, resize the board
                                           to according to the gridsize, and save the Sudoku puzzle and
                                           the grid size
     @param filename [Path of the Sudoku puzzle file]
     @param grid_size [Size (column length) of Sudoku puzzle board]
     */
    SudokuSerial(const std::string& filename, int& grid_size) : Sudoku(filename, grid_size) {}
    SudokuSerial(const Sudoku& s) : Sudoku(s) {} // deepcopy
    virtual void solve(int row=0, int col=0);
    void print();
};

#endif
