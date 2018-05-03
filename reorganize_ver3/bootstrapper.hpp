/**
 @file bootstrapper.hpp
 @brief Header file for the bootstrapper
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

#include <deque>
#include "board_deque.hpp"

/**
 @class Bootstrapper
 @brief Derived class of BoardDeque, a class to propagate possible boards of solutions and divide one Sudoku problem into several simpler subproblems
 
 This is an inherited class of the BoardDeque class. It has two constructors, three public methods, and two protected variables.
 */
class Bootstrapper: public BoardDeque {

public:
    /* Default constructor of class Bootstrapper */
    Bootstrapper(): BoardDeque() {}
    /** Constructor of class Bootstrapper: construct by calling the BoardDeque class's constructor
     @param b [a board]
     */
    Bootstrapper(const Board& b): BoardDeque(b) {}
    /** Get all solutions
     @return qsol [a BoardDeque object containing all solutions]
     */
    BoardDeque& solutions() { return qsol; }
    void bootstrap();
    /** Push a board to the deque and bootsrap
     @param b [a board]
     */
    void bootstrap(Board& b) {
        push_front(b);
        bootstrap();
    }
protected:
    std::deque<int> qsafe;
    BoardDeque qsol;
};

#endif
