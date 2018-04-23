/**
 @file solver.hpp
 @author Yiqi Xie
 @date April 20, 2018
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include "board.hpp"
#include "board_deque.hpp"


class Solver: public BoardDeque {
/* A solver class for sudoku problems */
public:
    // solves sudoku board b completely
    Solver(): BoardDeque() {}
    Solver(const Board& b): BoardDeque(b) {}
    void solve(Board& b, int r=0, int c=0);
    void solve() { 
        if (size() > 0) {
            solve(front()); 
            pop_front();
        }
    }
};


#endif