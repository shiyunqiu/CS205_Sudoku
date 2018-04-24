/**
 @file solver.hpp
 @brief Header file for the Sudoku solver.
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include "board.hpp"
#include "board_deque.hpp"

/**
 @class Solver
 @brief Derived class of BoardDeque, a class to solve Sudoku puzzle problems.
 
 This is an inherited class of the BoardDeque class. It has two constructors and two public methods.
 */
class Solver: public BoardDeque {

public:
    /* Default constructor */
    Solver(): BoardDeque() {}
    /** Constructor of class Solver: construct by calling the BoardDeque class's constructor
     @param b [a board]
     */
    Solver(const Board& b): BoardDeque(b) {}
    void solve(Board& b, int r=0, int c=0);
    /* Solve all boards one by one. */
    void solve() { 
        if (size() > 0) {
            solve(front()); 
            pop_front();
        }
    }
};


#endif
