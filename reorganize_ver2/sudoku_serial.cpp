#include <iostream>
#include <ctime>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "sudoku.hpp"
#include "sudoku_serial.hpp"


void SudokuSerial::task_begin() { 
    read(board); 
    std::cout << "Problem Board: " << std::endl;
    board.output(std::cout);
}

void SudokuSerial::task_process() {
    Solver solver(board);
    solver.solve();
    solver.dump(solutions);
}

void SudokuSerial::task_end() {
    write(solutions); 
    std::cout << "Solution Board(s): " << std::endl;
    solutions.output(std::cout);
}

void SudokuSerial::timer_start() {
    t_start = clock();
}

void SudokuSerial::timer_stop() {
    t_stop = clock();
    std::cout << "Elapsed in ";
    std::cout << double(t_stop-t_start)/CLOCKS_PER_SEC << " ";
    std::cout << "seconds (CPU)" << std::endl << std::endl;
}