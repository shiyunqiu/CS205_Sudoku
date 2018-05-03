/**
 @file sudoku_serial.cpp
 @brief Implementation for the serial class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Solve the Sudoku puzzle sequentially by trying all possible numbers in all empty cells.
 */

#include <iostream>
#include <ctime>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "sudoku_serial.hpp"

/* Read the content of a puzzle file, and output the board. */
void SudokuSerial::task_begin() { 
    read(board); 
    std::cout << "Problem Board: " << std::endl;
    board.output(std::cout);
}

/* Solve the Sudoku puzzle and save the solution in a deque of boards. */
void SudokuSerial::task_process() {
    Solver solver(board);
    solver.solve();
    solver.dump(solutions);
}

/* Write the solutions to a file and print out the solution boards. */
void SudokuSerial::task_end() {
    write(solutions); 
    std::cout << "Solution Board(s): " << std::endl;
    solutions.output(std::cout);
}

/* Start of the timer. */
void SudokuSerial::timer_start() {
    t_start = clock();
}

/* End of the timer and show elapsed time of execution. */
void SudokuSerial::timer_stop() {
    t_stop = clock();
    std::cout << "Elapsed in ";
    std::cout << double(t_stop-t_start)/CLOCKS_PER_SEC << " ";
    std::cout << "seconds (CPU)" << std::endl << std::endl;
}
