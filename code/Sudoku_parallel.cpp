/**
 @file Sudoku_parallel.cpp
 @brief Implementation for the serial class
 @author Shiyun Qiu, Yiqi Xie, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 OpenMP version of the Sudoku solver. Bootstrapping the board. The number of potential boards is determined by an interpolation function and all the boards are pushed into a deque to be solved in parallel.
 */

#include <iostream>
#include "Sudoku_parallel.hpp"
#include "Sudoku_serial.hpp"
#include <vector>

/** bootstrapping the Sudoku board, and push the generated boards to a deque */
void SudokuParallel::generate()
{
    int size = starts.size();
    for (int n=0; n<size; ++n) {
        const SudokuSerial& s = starts.front();
        int gen = 0;
        for (int i=0; i<grid_size; i++){
            for (int j=0; j<grid_size; j++){
                if (s.board[i][j]==0){
                    // fill in all possible values
                    for (int val=1; val<=grid_size; val++){
                        if (s.safe(i, j, val)){
                            starts.push_back(SudokuSerial(s)); // a deep copy
                            starts.back().board[i][j]=val;
                            gen++;
                        }
                    }
                }
                // ensure only 1 cell is filled
                if (gen>0) break;
            }
            // ensure only 1 cell is filled
            if (gen>0) break;
        }
        // fill one more cell
        if (gen!=0) starts.pop_front();
    }
}

/** analyze the board to determine the amount of bootstrapping to do */
void SudokuParallel::analyze()
{
    // Count the number of zeros in the board
    int nz = 0;
    for (int i=0; i<grid_size; ++i){
        for (int j=0; j<grid_size; ++j){
            if (board[i][j]==0) nz++;
        }
    }
    // Interpolation
    // ngen = 4+(4.-13.)/(53.-64.)*(nz-53);
    ngen = 8;
}

/** solve the sudoku puzzle. A thread solves one board in the deque, and the thread that
       finishes early will solve the next board left in the deque.
 */
void SudokuParallel::solve()
{
    // push the original board to start the generate process
    starts.emplace_back(SudokuSerial(*this)); // a deep copy
    for (int i=0; i<ngen; ++i) generate();
    
    // Solve starting from each of these boards in parallel
    int size = starts.size();
    std::cout << "queue size = " << size << std::endl;
    #pragma omp parallel for schedule(dynamic)
    for (int i=0; i<size; ++i){
        starts[i].solve();
    }
}










