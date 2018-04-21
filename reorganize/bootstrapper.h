/**
 @file solver.h
 @author Yiqi Xie
 @date April 21, 2018
 */

#ifndef BOOTSTRAPPER_H
#define BOOTSTRAPPER_H

#include <deque>
#include "board_container.h"
#include "board_queue.h"

class Bootstrapper {
/*
    A depth first search algorithm for sudoku solutions

*/
public:
    Bootstrapper() {}
    // takes a container of problems, does depth first search, adds search results back
    // if applied repeately for enough number of rounds, can arrive at the final solutions
    // the returning value is a boolean indicating if final solution is arrived in this round
    // this algorithm should work on both queue and stack
    bool bootstrap(BoardContainer& probs); 
public:
// protected:
    // some predefined cache structure for runtime acceleration
    BoardQueue cache_cboard;
    std::deque<int> cache_safenum;
};

#endif