/**
 @file board_queue.h
 @author Yiqi Xie
 @date April 20, 2018
 */

#ifndef BOARDQUEUE_H
#define BOARDQUEUE_H

#include <deque>
#include "board.h"
#include "board_container.h"

class BoardQueue: public BoardContainer {
/* 
    A deque implementation of BoardContainer 
    Though index accessing is allowed, it's not optimized for efficiency

 */
public:
    BoardQueue() {}
    BoardQueue(const Board& b); // initialize with a copy
    virtual int size() const;
    // virtual Board& head();
    // virtual void pop();
    // virtual void push(const Board& b);
    // virtual void pass(BoardContainer& bc);
    Board& operator[] (int i); // not recommended
    virtual void output(std::ostream& out=std::cout);
    ~BoardQueue();
public:
// protected:
    virtual Board* pt_head();
    virtual void pt_pop();
    virtual void pt_push(Board* pb);
protected:
    std::deque<Board*> queue;
};

#endif