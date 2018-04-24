#include <deque>
#include "board.hpp"
#include "board_deque.hpp"
#include "bootstrapper.hpp"


void Bootstrapper::bootstrap() {

    // if there is no start, return
    if (size() <= 0) {
        return;
    }

    Board& fboard = front();

    // if there is no empty cell, we get a solution
    int iempty = -1;
    int bsize = fboard.get_size();
    for (int i = 0; i < bsize*bsize; i++) {
        if (fboard.as_array()[i] == 0) {
            iempty = i;
            break;
        }
    }
    if (iempty < 0) {
        passFB(qsol);
        return;
    }

    // if the empty cell is not safe for all, we get a dead-end
    int rempty = iempty / bsize;
    int cempty = iempty % bsize;
    for (int n = 1; n <= bsize; n++) {
        if (fboard.safe(rempty, cempty, n)) {
            qsafe.push_back(n);
        }
    }
    if (qsafe.size() <= 0) {
        pop_front();
        return;
    }

    // generate subproblems and add them to the back
    while (qsafe.size() > 0) {
        fboard[rempty][cempty] = qsafe.front();
        if (qsafe.size() > 1) {
            push_back(fboard);
        } else {
            passFB(*this);
        }
        qsafe.pop_front();
    }
    return;
}




