#include <deque>
#include "board.h"
#include "board_container.h"
#include "board_queue.h"


// BoardQueue::BoardQueue() {}

BoardQueue::BoardQueue(const Board& b) { 
    Board* pbnew = new Board(b);
    queue.push_back(pbnew); 
}

BoardQueue::~BoardQueue() {
    while (queue.size() > 0) {
        delete queue.front();
        queue.pop_front();
    }
}

int BoardQueue::size() const {
    return queue.size(); 
}

Board* BoardQueue::pt_head() { 
    return queue.front();
}

void BoardQueue::pt_pop() {
    queue.pop_front(); 
}

void BoardQueue::pt_push(Board* pb) { 
    queue.push_back(pb); 
}

Board& BoardQueue::operator[] (int i) {
    return *(queue[i]);
}

void BoardQueue::output(std::ostream& out) {
    int i = 0;
    BoardQueue collect;
    while (size() > 0) {
        out << std::endl << "BOARD-" << ++i << std::endl;
        head().output();
        pass(collect);
    }
    while (collect.size() > 0) {
        collect.pass(*this);
    }
}