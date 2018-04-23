/**
 @file sudoku.hpp
 @author Yiqi Xie
 @date April 23, 2018
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <fstream>
#include "board.hpp"
#include "board_deque.hpp"


class Sudoku {
public:
    void run() {
        task_begin();
        timer_start();
        task_assign();
        task_process();
        task_collect();
        timer_stop();
        task_end();
    }
    static void read(Board& b);
    static void write(BoardDeque& bq);

public:
    static int BSIZE;
    static std::string IFILE_NAME;
    static std::string OFILE_NAME;

protected:
    virtual void task_begin() {}
    virtual void task_assign() {}
    virtual void task_process() {}
    virtual void task_collect() {}
    virtual void task_end() {}
    virtual void timer_start() {}
    virtual void timer_stop() {}
};


#endif