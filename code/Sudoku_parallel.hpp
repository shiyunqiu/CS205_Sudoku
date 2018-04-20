/**
 @file Sudoku_parallel.hpp
 @brief Header file for the parallel class
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SUDOKU_PARALLEL_HPP
#define SUDOKU_PARALLEL_HPP

#include "Sudoku.hpp"
#include "Sudoku_serial.hpp"
#include <deque>

/**
 @class SudokuParallel
 @brief Derived class of Sudoku, OpenMP version of the Sudoku Solver
 
 This is an inherited class of the Sudoku class. It has three constructors, three functions, and two member variables. It inherits two functions and two variables from the base class.
 */
class SudokuParallel : public Sudoku {
public:
    SudokuParallel() : Sudoku() {}
    /** constructor of class SudokuParallel: save the Sudoku puzzle and the grid size of the puzzle board,
                                             and call analyze function to determine the amount of bootstrapping
     @param board [Sudoku puzzle board]
     @param grid_size [Size (column length) of Sudoku puzzle board]
     */
    SudokuParallel(const std::vector<std::vector<int> >& board, int& grid_size) : Sudoku(board, grid_size) { analyze(); }
    /** constructor of class SudokuParallel: read Sudoku puzzle problem from a sdk file, resize the board
                                             to according to the gridsize, save the Sudoku puzzle and
                                             the grid size, and call analyze function to determine the amount
                                             of bootstrapping
     @param filename [Path of the Sudoku puzzle file]
     @param grid_size [Size (column length) of Sudoku puzzle board]
     */
    SudokuParallel(const std::string& filename, int& grid_size) : Sudoku(filename, grid_size) { analyze(); }
    virtual void solve();
protected:
    void analyze();
    void generate();
    int ngen; //amount of bootstrapping
    std::deque<SudokuSerial> starts; // queue of boards for parallelization
};

#endif
