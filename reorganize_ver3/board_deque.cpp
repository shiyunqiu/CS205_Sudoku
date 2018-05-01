/**
 @file board_deque.cpp
 @brief A wrapper for std::deque<*Boards>
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Define a queue of boards to help the implementation of the OpenMP version and MPI version of the solver.
 */
#include <deque>
#include <vector>
#include <algorithm>
#include <random>
#include "board.hpp"
#include "board_deque.hpp"

/** Constructor of class BoardDeque: construct a new BoardDeque by saving the board b as its firast element
 @param b [a board]
 */
BoardDeque::BoardDeque(const Board& b) { 
    Board* pbnew = new Board(b);
    bdeque.push_back(pbnew); 
}

/* Destructor of class BoardDeque: delete the array inside the deque one by one. */
BoardDeque::~BoardDeque() {
    while (bdeque.size() > 0) {
        delete bdeque.front();
        bdeque.pop_front();
    }
}

/** Get the size of the deque
 @return [number of boards in the deque]
 */
int BoardDeque::size() const { return bdeque.size(); }

/** Get the first board in the deque
 @return [the first board in the deque]
 */
Board& BoardDeque::front() { return *(bdeque.front()); } 

/** Get the last board in the deque
 @return [the last board in the deque]
 */
Board& BoardDeque::back() { return *(bdeque.back()); } 

/** Get the ith board in the deque
 @param i [index of the board]
 @return [the ith board in the deque]
 */
Board& BoardDeque::operator[] (int i) { return *(bdeque[i]); }

/* Remove the first board in the deque and release memory. */
void BoardDeque::pop_front() {
    delete bdeque.front();
    bdeque.pop_front();
}

/* Remove the last board in the deque and release memory. */
void BoardDeque::pop_back() {
    delete bdeque.back();
    bdeque.pop_back();
}

/** Push a board to the front of the deque
 @param b [a board]
 */
void BoardDeque::push_front(const Board& b) {
    Board* pb_new = new Board(b); 
    bdeque.push_front(pb_new);
}

/** Push a board to the end of the deque
 @param b [a board]
 */
void BoardDeque::push_back(const Board& b) {
    Board* pb_new = new Board(b); 
    bdeque.push_back(pb_new);
}

/** Push the first board of this BoardDeque object to the end of another BoardDeque object
 @param bq [a BoardDeque object]
 */
void BoardDeque::passFB(BoardDeque& bq) {
    bq.bdeque.push_back(bdeque.front());
    bdeque.pop_front();
}

/** Push the first board of this BoardDeque object to the front of another BoardDeque object
 @param bq [a BoardDeque object]
 */
void BoardDeque::passFF(BoardDeque& bq) {
    bq.bdeque.push_front(bdeque.front());
    bdeque.pop_front();
}

/** Push the last board of this BoardDeque object to the front of another BoardDeque object
 @param bq [a BoardDeque object]
 */
void BoardDeque::passBF(BoardDeque& bq) {
    bq.bdeque.push_front(bdeque.back());
    bdeque.pop_back();
}

/** Push the last board of this BoardDeque object to the end of another BoardDeque object
 @param bq [a BoardDeque object]
 */
void BoardDeque::passBB(BoardDeque& bq) {
    bq.bdeque.push_back(bdeque.back());
    bdeque.pop_back();
}

/** Write the board to a file/console in order
 @param out [the stream to output data to]
 */
void BoardDeque::output(std::ostream& out) {
    int i = 0;
    BoardDeque collect;
    while (size() > 0) {
        out << std::endl << "BOARD-" << ++i << std::endl;
        front().output(out);
        passFB(collect);
    }
    while (collect.size() > 0) {
        collect.passFB(*this);
    }
}


void BoardDeque::shuffle(unsigned seed) {
    int n = bdeque.size();
    std::vector<Board*> tmpvec(n);
    for (int i = 0; i < n; ++i) {
        tmpvec[i] = bdeque.front();
        bdeque.pop_front();
    }
    std::shuffle(tmpvec.begin(), tmpvec.end(), std::default_random_engine(seed));
    for (std::vector<Board*>::iterator it = tmpvec.begin(); it != tmpvec.end(); ++it) {
        bdeque.push_back(*it);
    }
}