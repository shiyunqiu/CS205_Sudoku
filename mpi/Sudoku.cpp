/**
 @file Sudoku.cpp
 @brief Implementation for base class
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Sudoku.hpp"


/** default constructor of class Sudoku: assign grid_size as 0 */
Sudoku::Sudoku() :
grid_size(0)
{
}

/** constructor of class Sudoku: save the Sudoku puzzle and the grid size of the puzzle board
 @param board_pass [Sudoku puzzle board]
 @param grid_size [Size (column length) of Sudoku puzzle board]
 */
Sudoku::Sudoku(const std::vector<std::vector<int> >& board_pass, int& grid_size):
board(board_pass), grid_size(grid_size)
{
}

/** constructor of class Sudoku: read Sudoku puzzle problem from a sdk file, resize the board
                                 to according to the gridsize, and save the Sudoku puzzle and
                                 the grid size
 @param filename [Path of the Sudoku puzzle file]
 @param grid_size [Size (column length) of Sudoku puzzle board]
 */
Sudoku::Sudoku(const std::string& filename, int& grid_size):
grid_size(grid_size)
{
    board.resize(grid_size);
    for (int i = 0; i < grid_size; i++)
        board[i].resize(grid_size);
    load(filename);
}

/** copy constructor of class Sudoku: copy grid size and the board
 @param s [A Sudoku class object]
 */
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

Sudoku::Sudoku(const int* array, int& grid_size): 
grid_size(grid_size)
{
    board.resize(grid_size);
    for (int i = 0; i < grid_size; i++) {
        board[i].resize(grid_size);
        for (int j = 0; j < grid_size; j++) {
            board[i][j] = array[i*grid_size+j];
        }
    }
}

void Sudoku::to_array(int* array) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j< grid_size; j++) {
            array[i*grid_size+j] = board[i][j];
        }
    }
}

/** load a Sudoku board from a file
 @param  filename [The file to load]
 */
void Sudoku::load(const std::string& filename)
{
    std::ifstream file(filename);
    // if no file exists, error message
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
            // grid size of the board in the file not matching the given grid size
            if (++i>grid_size || j>grid_size) {
                printf("%d %d\n", i, j);
                std::cerr << "Error: malformed file" << std::endl;
                exit(1);
            }
        }
    }
}

/** check if a value can be put at a certain position on the board
 @param col [column number]
 @param row [row number]
 @param n [value to be checked]
 @return 1/0 [1 indicates the value can be put in this position, 0 otherwise]
 */
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


