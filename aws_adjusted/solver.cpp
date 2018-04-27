/**
 @file solver.cpp
 @brief Find all solutions for a Sudoku puzzle board
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Brutal force solver using depth first search and recursion.
 */
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"

/** Solve the Sudoku puzzle by recursion
 @param b [a board to be solved]
 @param r [row number]
 @param c [column number]
 */
void Solver::solve(Board& b, int r, int c) {

    int abs_index = r * b.get_size() + c;
    // solved
    if (abs_index >= b.get_ncell()) {
        push_back(b); 
    }
    else {
        int t;
        int r_next = (abs_index + 1) / b.get_size();
        int c_next = (abs_index + 1) % b.get_size();
        // fill in all possible numbers
        for (int n = 1; n <= b.get_size(); n++) {
            if (b.safe(r, c, n)) {
                t = b[r][c];
                b[r][c] = n;
                // recursion
                solve(b, r_next, c_next);
                b[r][c] = t;
            }
        }
    }
}

