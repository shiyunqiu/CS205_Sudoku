/**
 @file sudoku.hpp
 @author Yiqi Xie
 @date April 23, 2018
 */


#ifndef SUDOKU_SERIAL_H
#define SUDOKU_SERIAL_H

#include "board.hpp"
#include "board_deque.hpp"
#include "sudoku.hpp"


class SudokuSerial: public Sudoku {
public:
    SudokuSerial(): board(Board(BSIZE)) {}
    SudokuSerial(int argc, char** argv): SudokuSerial() {}
protected:
    virtual void task_begin();
    virtual void task_process();
    virtual void task_end();
    virtual void timer_start();
    virtual void timer_stop();
protected:
    Board board;
    BoardDeque solutions;
    clock_t t_start, t_stop;
};

#endif