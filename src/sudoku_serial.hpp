/**
 @file sudoku_serial.hpp
 @brief Header file for the serial class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */


#ifndef SUDOKU_SERIAL_H
#define SUDOKU_SERIAL_H

#include "board.hpp"
#include "board_deque.hpp"
#include "sudoku.hpp"

/**
 @class SudokuSerial
 @brief Derived class of Sudoku, serial version of the Sudoku Solver
 
 This is an inherited class of the Sudoku class. It has two constructors, five protected functions, and four protected variables.
 */
class SudokuSerial: public Sudoku {
public:
    SudokuSerial(): board(Board(BSIZE)) {
        std::cout << "Sudoku Serial started" << std::endl << std::endl;
    }
    SudokuSerial(int argc, char** argv): SudokuSerial() {}
protected:
    virtual void task_begin();
    virtual void task_process();
    virtual void task_end();
    virtual void timer_start();
    virtual void timer_stop();

    Board board;
    BoardDeque solutions;
    clock_t t_start, t_stop;
};

#endif
