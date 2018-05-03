/**
 @file sudoku_queue_scheme.hpp
 @brief Header file for queue construction
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */

#ifndef SUDOKU_QUEUE_SCHEME_H
#define SUDOKU_QUEUE_SCHEME_H

#include <omp.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "sudoku.hpp"

/**
 @class SudokuQueueScheme
 @brief Derived class of Sudoku, construct a queue of boards for parallelism
 
 This is an inherited class of the Sudoku class. It has two constructors, seven public functions, two public variables, and five protected variables.
 */
class SudokuQueueScheme: public Sudoku {
public:
    SudokuQueueScheme(): board(BSIZE) {};
    SudokuQueueScheme(int argc, char** argv): board(BSIZE) {
        omp_set_dynamic(0);
        omp_set_num_threads(THREAD_NUM);
        #pragma omp parallel
        {
            #pragma omp single
            {
                n_thread = omp_get_num_threads(); 
                std::cout << "OMP Number of Threads: ";
                std::cout << n_thread << std::endl << std::endl;
            }
        }
    }
public:
    static int THREAD_NUM;
    static int BOOTSTRAP_NUM;
protected:
    virtual void task_begin();
    virtual void task_process();
    virtual void task_end();
    virtual void timer_start();
    virtual void timer_stop();
protected:
    int n_thread;
    double t_start, t_stop;
    Board board;
    BoardDeque solutions;
};


#endif
