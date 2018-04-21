/**
 @file board_container.h
 @author Yiqi Xie
 @date April 20, 2018
 */

#ifndef BOARDCONTAINER_H
#define BOARDCONTAINER_H

#include <iostream>
#include "board.h"

class BoardContainer {
/*
    An abstact container class for sudoku boards

    The main features are:
     - number of elements:              container.size()
     - access to the "first" element:   container.head()
     - discard the "first" element:     container.pop()
     - add to the "end":                container.push()
     - discard the "first" element and add it to the "end" 
       of another container:            container1.pass(container2)
     - output to std::ostream:          container.output(std::cout)
    
    To improve data transfer efficiency, the elements are board pointers
    A BoardContainer objects has the ownership of its boards
    In specific, at user-interface level:
     - elements are added in copies, 
     - elements are accessed in references or copies, 
     - elements are destructed during the destruction of the container.

 */
public:
    // returns the number of elements in the container
    virtual int size() const = 0;
    // returns the "first" element's reference
    virtual Board& head() { return *(pt_head()); } 
    // pops the "first" element
    virtual void pop() {
        delete pt_head();
        pt_pop();
    }
    // pushes in a deepcopy
    virtual void push(const Board& b) {
        Board* pb_new = new Board(b); 
        pt_push(pb_new);
    }
    // pass the ownership of one board to another container without copying it
    virtual void pass(BoardContainer& bc) {
        bc.pt_push(pt_head());
        pt_pop();
    }
    // output all elements; may change the container during the process, but should recover it in the end.
    virtual void output(std::ostream& out=std::cout) {
        out << "this class has not implemented the output method. " << std::endl;
    }
public:
// protected:
    virtual Board* pt_head() = 0;
    virtual void pt_pop() = 0;
    virtual void pt_push(Board* pb) = 0;
};

#endif