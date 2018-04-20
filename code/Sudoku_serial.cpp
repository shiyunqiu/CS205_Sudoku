/**
 @file Sudoku_serial.cpp
 @brief Implementation for the serial class
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Brutal force solver using depth first search and recursion.
 */

#include <iostream>
#include <cmath>
#include "Sudoku_serial.hpp"

/** solve the sudoku puzzle by recursion
 @param col [column number]
 @param row [row number]
*/
void SudokuSerial::solve(int row, int col){
    int n, t;
    // all possibilities exlored
    if (row == grid_size)
        print();
    else{
        for (n = 1; n <= grid_size; n++){
            // check possible values
            if (safe(row, col, n)) {
                t = board[row][col];
                board[row][col] = n;
                //prevent index out of bound
                if (col == grid_size-1)
                    solve(row + 1, 0);
                else
                    solve(row, col + 1);
                board[row][col] = t;
            }
        }
    }
}

/** print the board */
void SudokuSerial::print()
{
    // initialize the variable at the first call
    static int nsol = 0;
    int r, c;
    int small_grid = sqrt(grid_size);
    std::cout << "solution " << ++nsol <<std::endl;
    for (r = 0; r < grid_size; r++)
    {
        for (c = 0; c < grid_size; c++)
        {
            std::cout << board[r][c] << " ";
            if (c % small_grid == (small_grid-1)) std::cout << "  ";
        }
        std::cout << "\n";
        if (r % small_grid == (small_grid-1)) std::cout << "\n";
    }
    
}
