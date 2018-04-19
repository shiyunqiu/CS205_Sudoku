//
//  Sudoku.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Sudoku.hpp"

Sudoku::Sudoku() :
grid_size(0)
{
}

Sudoku::Sudoku(const std::vector<std::vector<int> >& board_pass, int& grid_size):
board(board_pass), grid_size(grid_size)
{
}

Sudoku::Sudoku(const std::string& filename, int& grid_size):
grid_size(grid_size)
{
    board.resize(grid_size);
    for (int i = 0; i < grid_size; i++)
        board[i].resize(grid_size);
    load(filename);
}

Sudoku::Sudoku(const Sudoku& s):
grid_size(s.grid_size)
{
    board.resize(grid_size);
    for (int i = 0; i < grid_size; i++) {
        board[i].resize(grid_size);
        for (int j = 0; j < grid_size; j++) {
            board[i][j] = s.board[i][j];
        }
    }
}

/** Load a Sudoku board from a file.
 * \param[in] filename : The file to load. */
void Sudoku::load(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    } else {
        std::string line;
        int i=0;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            int j=0;
            while (ss >> board[i][j]){
                if(j<grid_size){
                    j++;
                }
                else{
                    j = 0;
                    i++;
                }
            }
            if (++i>grid_size || j>grid_size) {
                printf("%d %d\n", i, j);
                std::cerr << "Error: malformed file" << std::endl;
                exit(1);
            }
        }
    }
}

int Sudoku::safe(int row, int col, int n) const
{
    int r, c, br, bc;
    int small_grid = sqrt(grid_size);
    if (board[row][col] == n) return 1;
    if (board[row][col] != 0) return 0;
    for (c = 0; c < grid_size; c++)
        if (board[row][c] == n) return 0;
    for (r = 0; r < grid_size; r++)
        if (board[r][col] == n) return 0;
    br = row / small_grid;
    bc = col / small_grid;
    for (r = br * small_grid; r < (br + 1) * small_grid; r++)
        for (c = bc * small_grid; c < (bc + 1) * small_grid; c++)
            if (board[r][c] == n) return 0;
    return 1;
}


