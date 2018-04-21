#include <deque>
#include "board.h"
#include "board_container.h"
#include "bootstrapper.h"


// Bootstrapper::Bootstrapper() {}


bool Bootstrapper::bootstrap(BoardContainer& probs) {
    // this algorithm should work on both queue and stack
    // i.e. pop before push

    bool progressed = false;
    bool solved = true;
    int size = probs.head().get_size();

    for (int row = 0; row < size; row++) {

        for (int col = 0; col < size; col++) {
            Board& cboard = probs.head();

            if (cboard[row][col] == 0) {
                solved = false; 
                probs.pass(cache_cboard);
                for (int n = 1; n <= size; n++) {
                    if (cboard.safe(row, col, n))
                        cache_safenum.push_back(n);
                }
                while (cache_safenum.size() > 0) {
                    cboard[row][col] = cache_safenum.front();
                    cache_safenum.pop_front();
                    if (cache_safenum.size() <= 0)
                        cache_cboard.pass(probs);
                    else
                        probs.push(cboard);
                    progressed = true;
                }
                while (cache_cboard.size() > 0) {
                    cache_cboard.pop();
                }
            }

            if (progressed) break;
        }
        if (progressed) break;
    }

    return solved;
}