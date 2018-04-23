/**
 @file board_container.h
 @author Yiqi Xie
 @date April 22, 2018
 */

#ifndef BOARD_DEQUE_H
#define BOARD_DEQUE_H

#include <iostream>
#include <deque>
#include "board.hpp"

class BoardDeque: public std::deque<Board> {
/*
    A wrapper for std::deque<*Boards>
    
    A BoardDeque object is designed to have full ownership of its elements
    Ideally, at user-interface level:
     - elements are added as copies, 
     - elements are accessed as references or copies, 
     - elements are destructed during the destruction of the container.

 */
public:
    BoardDeque() {}
    // starts with a copy
    BoardDeque(const Board& b);
    // destructor also destruct the boards
    virtual ~BoardDeque(); 
    // returns the number of boards
    virtual int size() const;
    // access the board at each end
    virtual Board& front();
    virtual Board& back();
    // index accessing, not recommended
    virtual Board& operator[] (int i);
    // pop and destruct the board
    virtual void pop_front();
    virtual void pop_back();
    // push a deepcopy
    virtual void push_front(const Board& b);
    virtual void push_back(const Board& b);
    // pass the ownership of one board to another container without copying it
    virtual void passFB(BoardDeque& bq); // pop_front to push_back
    virtual void passFF(BoardDeque& bq); // pop_front to push_front
    virtual void passBF(BoardDeque& bq); // pop_back to push front
    virtual void passBB(BoardDeque& bq); // pop_back to push back
    // output all elements
    virtual void output(std::ostream& out=std::cout);
    // some shorthand settings, by default they behaves like a queue (back in front out)
    virtual void pop() { pop_front(); }
    virtual void push(const Board& b) { push_back(b); }
    virtual void pass(BoardDeque& bq) { passFB(bq); }
    virtual void dump(BoardDeque& bq, int len=-1) { while (len-- != 0 && size() > 0) passFB(bq); } 
public:
// protected:
    std::deque<Board*> bdeque;
};

#endif