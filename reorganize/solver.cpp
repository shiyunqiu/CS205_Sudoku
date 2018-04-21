#include "board.h"
#include "board_container.h"
#include "solver.h"


void Solver::solve(Board& b, BoardContainer& sols, int row, int col) {

    int abs_index = row * b.get_size() + col;

    if (abs_index >= b.get_ncell()) {
        sols.push(b);
    }
    else {
        int t;
        int row_next = (abs_index + 1) / b.get_size();
        int col_next = (abs_index + 1) % b.get_size();

        for (int n = 1; n <= b.get_size(); n++) {
            if (b.safe(row, col, n)) {
                t = b[row][col];
                b[row][col] = n;
                solve(b, sols, row_next, col_next);
                b[row][col] = t;
            }
        }
    }
}