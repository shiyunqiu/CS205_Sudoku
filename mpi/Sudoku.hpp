/**
 @file Sudoku.hpp
 @brief Header file for base class
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <string>
#include <vector>

/**
 @class Sudoku
 @brief Base class
 
 This class is a base class for the inherited classes Sudoku_serial and Sudoku_parallel. It has three constructors, one copy constructor, two public functions and two member variables.
*/
class Sudoku {
public:
    Sudoku();
    Sudoku(const std::vector<std::vector<int> >& board_pass, int& grid_size);
    Sudoku(const std::string& filename, int& grid_size);
    Sudoku(const Sudoku& s); // deepcopy
    Sudoku(const int* array, int& grid_size); // construct from an int array
    void to_array(int* array); // export to an int array
    void load(const std::string& filename);
    int safe(int row, int col, int n) const;
    int grid_size;
    std::vector<std::vector<int> > board;
};
#endif
