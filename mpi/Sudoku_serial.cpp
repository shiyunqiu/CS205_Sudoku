//
//  Sudoku_serial.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Sudoku_serial.hpp"


void SudokuSerial::solve(int row, int col){
    int n, t;
    if (row == grid_size)
        print();
    else{
        for (n = 1; n <= grid_size; n++){
            if (safe(row, col, n)) {
                t = board[row][col];
                board[row][col] = n;
                if (col == grid_size-1)
                    solve(row + 1, 0);
                else
                    solve(row, col + 1);
                board[row][col] = t;
            }
        }
    }
}

/** Print the board. */
void SudokuSerial::print()
{
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
