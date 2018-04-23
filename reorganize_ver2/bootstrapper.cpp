#include <deque>
#include "board.hpp"
#include "board_deque.hpp"
#include "bootstrapper.hpp"


void Bootstrapper::bootstrap() {

    if (size() <= 0) return;

    bool solved = true; 
    bool progressed = false;

    int size = front().get_size();

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Board& tboard = front();

            if (tboard[row][col] == 0) {
                solved = false; 
                passFB(qtmp);

                for (int n = 1; n <= size; n++) {
                    if (tboard.safe(row, col, n)) {
                        qsafe.push_back(n);
                    }
                }
                while (qsafe.size() > 0) {
                    tboard[row][col] = qsafe.front();
                    qsafe.pop_front();
                    if (qsafe.size() <= 0)
                        qtmp.passBB(*this);
                    else
                        push_back(tboard);
                    progressed = true;
                }
                while (qtmp.size() > 0) {
                    qtmp.pop_front();
                }
            }
            if (progressed) break;
        }
        if (progressed) break;
    }
    if (solved) {
        passFB(qsol);
    }
}