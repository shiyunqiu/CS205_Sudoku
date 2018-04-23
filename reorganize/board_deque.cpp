#include <deque>
#include "board.hpp"
#include "board_deque.hpp"


BoardDeque::BoardDeque(const Board& b) { 
    Board* pbnew = new Board(b);
    bdeque.push_back(pbnew); 
}

BoardDeque::~BoardDeque() {
    while (bdeque.size() > 0) {
        delete bdeque.front();
        bdeque.pop_front();
    }
}

int BoardDeque::size() const { return bdeque.size(); }

Board& BoardDeque::front() { return *(bdeque.front()); } 

Board& BoardDeque::back() { return *(bdeque.back()); } 

Board& BoardDeque::operator[] (int i) { return *(bdeque[i]); }

void BoardDeque::pop_front() {
    delete bdeque.front();
    bdeque.pop_front();
}

void BoardDeque::pop_back() {
    delete bdeque.back();
    bdeque.pop_back();
}

void BoardDeque::push_front(const Board& b) {
    Board* pb_new = new Board(b); 
    bdeque.push_front(pb_new);
}

void BoardDeque::push_back(const Board& b) {
    Board* pb_new = new Board(b); 
    bdeque.push_back(pb_new);
}

void BoardDeque::passFB(BoardDeque& bq) {
    bq.bdeque.push_back(bdeque.front());
    bdeque.pop_front();
}

void BoardDeque::passFF(BoardDeque& bq) {
    bq.bdeque.push_front(bdeque.front());
    bdeque.pop_front();
}

void BoardDeque::passBF(BoardDeque& bq) {
    bq.bdeque.push_front(bdeque.back());
    bdeque.pop_back();
}

void BoardDeque::passBB(BoardDeque& bq) {
    bq.bdeque.push_back(bdeque.back());
    bdeque.pop_back();
}

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