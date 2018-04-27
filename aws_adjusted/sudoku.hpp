/**
 @file sudoku.hpp
 @brief Header file for base class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <fstream>
#include "board.hpp"
#include "board_deque.hpp"

/**
 @class Sudoku
 @brief Base class
 
 This class is a base class for the inherited classes Sudoku_serial, Sudoku_parallel, SudokuQueueScheme, and SudokuMPI. It has three public functions, three public parameters, and seven protected methods. The seven protected methods are left empty in the base class and will be implemented in the inherited classes as needed.
 */
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
