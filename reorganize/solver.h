/**
 @file solver.h
 @author Yiqi Xie
 @date April 20, 2018
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include "board_container.h"


class Solver {
/*
    A solver class for sudoku problems, basically a function wrapper
 */
public:
    Solver() {}
    // take in sodoku b, and adds the solution (if any) to container sols
    void solve(Board& b, BoardContainer& sols, int row=0, int col=0); 
};

#endif