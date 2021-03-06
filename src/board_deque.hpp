/**
 @file board_deque.hpp
 @brief Header file for the BoardDeque class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef BOARD_DEQUE_H
#define BOARD_DEQUE_H

#include <iostream>
#include <deque>
#include "board.hpp"

/**
 @class BoardDeque
 @brief A wrapper for std::deque<*Boards>
 
 A BoardDeque object is designed to have full ownership of its elements
 Ideally, at user-interface level:
 - elements are added as copies,
 - elements are accessed as references or copies,
 - elements are destructed during the destruction of the container.
 
 This class has two constructors, one destructor, eighteen public methods, and one public variable.
 */
class BoardDeque: public std::deque<Board> {

public:
    BoardDeque() {}
    // starts with a copy
    BoardDeque(const Board& b);
    // returns the number of boards
    int size() const;
    // access the board at each end
    Board& front();
    Board& back();
    // index accessing, not recommended
    Board& operator[] (int i);
    // pop and destruct the board
    void pop_front();
    void pop_back();
    // push a deepcopy
    void push_front(const Board& b);
    void push_back(const Board& b);
    // pass the ownership of one board to another container without copying it
    void passFB(BoardDeque& bq); // pop_front to push_back
    void passFF(BoardDeque& bq); // pop_front to push_front
    void passBF(BoardDeque& bq); // pop_back to push front
    void passBB(BoardDeque& bq); // pop_back to push back
    // output all elements
    void output(std::ostream& out=std::cout);
    // shorthand functions
    /** pop first element in the deque */
    virtual void pop() { pop_front(); }
    /** Push a board to the end of the deque
     @param b [a Board object]
     */
    virtual void push(const Board& b) { push_back(b); }
    /** Push the first board of this BoardDeque object to the end of another BoardDeque object
     @param bq [a BoardDeque object]
     */
    virtual void pass(BoardDeque& bq) { passFB(bq); }
    /** Move boards in this BoardDeque object to another BoardDeque object in order
     @param bq [a BoardDeque object]
     @param len [number of boards to be moved]
     */
    virtual void dump(BoardDeque& bq, int len=-1) { while (len-- != 0 && size() > 0) passFB(bq); } 
    /** randomly shuffle the deque */
    virtual void shuffle(unsigned seed);
    // destructor also destruct the boards
    virtual ~BoardDeque(); 
public:
    std::deque<Board*> bdeque;
};

#endif
