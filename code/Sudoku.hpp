//
//  Header.h
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <string>
#include <vector>

/** A Sudoku solver. */
class Sudoku {
public:
    Sudoku();
    Sudoku(const std::vector<std::vector<int> >& board_pass, int& grid_size);
    Sudoku(const std::string& filename, int& grid_size);
    void load(const std::string& filename);
protected:
    int safe(int row, int col, int n);
    int grid_size;
    std::vector<std::vector<int> > board;
};

#endif
