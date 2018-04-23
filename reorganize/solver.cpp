#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"


void Solver::solve(Board& b, int r, int c) {

    int abs_index = r * b.get_size() + c;
    if (abs_index >= b.get_ncell()) {
        push_back(b); 
    }
    else {
        int t;
        int r_next = (abs_index + 1) / b.get_size();
        int c_next = (abs_index + 1) % b.get_size();

        for (int n = 1; n <= b.get_size(); n++) {
            if (b.safe(r, c, n)) {
                t = b[r][c];
                b[r][c] = n;
                solve(b, r_next, c_next);
                b[r][c] = t;
            }
        }
    }
}

