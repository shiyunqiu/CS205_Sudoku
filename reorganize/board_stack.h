/**
 @file board_stack.h
 @author Yiqi Xie
 @date April 21, 2018
 */

#ifndef BOARDSTACK_H
#define BOARDSTACK_H

#include <stack>
#include "board.h"
#include "board_container.h"

class BoardStack: public BoardContainer {
/* 
    A stack implementation of BoardContainer 
    
 */
public:
    BoardStack() {}
    BoardStack(const Board& b); // initialize with a copy
    virtual int size() const;
    // virtual Board& head();
    // virtual void pop();
    // virtual void push(const Board& b);
    // virtual void pass(BoardContainer& bc);
    virtual void output(std::ostream& out=std::cout);
    ~BoardStack();
public:
// protected:
    virtual Board* pt_head();
    virtual void pt_pop();
    virtual void pt_push(Board* pb);
protected:
    std::stack<Board*> stack;
};

#endif