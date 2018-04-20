//
//  Sudoku_parallel.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/18/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <iostream>
#include "Sudoku_parallel.hpp"
#include "Sudoku_serial.hpp"
#include <vector>


int SudokuParallel::SPNGEN = 1;


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
                        if (s.safe(i, j, val)){
                            starts.push_back(SudokuSerial(s)); // a deep copy
                            starts.back().board[i][j]=val;
                            gen++;
                        }
                    }
                }
                if (gen>0) break;
            }
            if (gen>0) break;
        }
        if (gen!=0) starts.pop_front();
    }
}

/** Analyze the board to determine the amount of bootstrapping to do. */
void SudokuParallel::analyze()
{
    if (SPNGEN < 1) {
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
    else {
        ngen = SPNGEN;
    }
}

void SudokuParallel::solve(bool warm_start)
{
    if (!warm_start) {
        starts.emplace_back(SudokuSerial(*this)); // a deep copy
    }
    for (int i=0; i<ngen; ++i) generate();
    
    // Solve starting from each of these boards in parallel
    int size = starts.size();
    std::cout << "omp queue size: " << size << std::endl;
    #pragma omp parallel for schedule(dynamic)
    for (int i=0; i < size; ++i) {
        starts.front().solve();
        SudokuSerial& ss = starts.front(); 
        while (ss.solutions.size() > 0) {
            solutions.push_back(ss.solutions.front());
            ss.solutions.pop_front();
        }
        starts.pop_front();
    }
}










