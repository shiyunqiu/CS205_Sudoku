#include <stack>
#include "board.h"
#include "board_container.h"
#include "board_stack.h"


// BoardStack::BoardStack() {}

BoardStack::BoardStack(const Board& b) { 
    Board* pbnew = new Board(b);
    stack.push(pbnew); 
}

BoardStack::~BoardStack() {
    while (stack.size() > 0) {
        delete stack.top();
        stack.pop();
    }
}

int BoardStack::size() const {
    return stack.size(); 
}

Board* BoardStack::pt_head() { 
    return stack.top();
}

void BoardStack::pt_pop() {
    stack.pop(); 
}

void BoardStack::pt_push(Board* pb) { 
    stack.push(pb); 
}

void BoardStack::output(std::ostream& out) {
    int i = 0;
    BoardStack collect;
    while (size() > 0) {
        out << std::endl << "BOARD-" << ++i << std::endl;
        head().output();
        pass(collect);
    }
    while (collect.size() > 0) {
        collect.pass(*this);
    }
}