/**
 @file solver.h
 @author Yiqi Xie
 @date April 21, 2018
 */

#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

#include <deque>
#include "board.hpp"
#include "board_deque.hpp"


class Bootstrapper: public BoardDeque {
/* bootstraper develops one sudoku problem into several subproblems */
public:
    Bootstrapper(): BoardDeque() {}
    Bootstrapper(const Board& b): BoardDeque(b) {}
    BoardDeque& solutions() { return qsol; }
    void bootstrap();
    void bootstrap(Board& b) {
        push_front(b);
        bootstrap();
    }
protected:
    std::deque<int> qsafe;
    BoardDeque qtmp;
    BoardDeque qsol;
};

#endif