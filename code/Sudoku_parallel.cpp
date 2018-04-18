//
//  Sudoku_parallel.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/18/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <iostream>
#include "Sudoku_parallel.hpp"
#include <vector>


void SudokuParallel::generate()
{
    int size = starts.size();
    for (int n=0; n<size; ++n) {
        const SudokuSerial& s = starts.front();
        int gen = 0;
        for (int i=0; i<grid_size; i++){
            for (int j=0; j<grid_size; j++){
                if (s.board[i][j]==0){
                    for (int val=1; val<=grid_size; val++){
                        int seen = s.safe(i, j, val);
                        if (seen==0){
                            starts.push_back(s);
                            starts.back().board[i][j]=val;
                            gen++;
                        }
                    }
                    if (gen>0) break;
                }
            }
        }
        if (gen!=0) starts.pop_front();
    }
}

/** Analyze the board to determine the amount of bootstrapping to do. */
void SudokuParallel::analyze()
{
    // Count the number of zeros in the board
    int nz = 0;
    for (int i=0; i<grid_size; ++i){
        for (int j=0; j<grid_size; ++j){
            if (board[i][j]==0) nz++;
        }
    }
    // How to do this interpolation?
    ngen = 4+(4.-13.)/(53.-64.)*(nz-53);
}


void SudokuParallel::solve(int row, int col)
{
    // Generate starting boards via breadth-first search
    starts.emplace_back(board);
    for (int i=0; i<ngen; ++i) generate();
    
    // Solve starting from each of these boards in parallel
    int size = starts.size();
    #pragma omp parallel for reduction(+:total)
    for (int i=0; i<size; ++i){
        starts[i].solve();
    }
}










