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
 
 This is an inherited class of the Sudoku class. It has two constructors, five protected functions, two public variables, and five protected variables.
 */
class SudokuQueueScheme: public Sudoku {
public:
    SudokuQueueScheme(): board(BSIZE) {};
    /** Constructor of class SudokuQueueScheme: set up and print out OMP number of threads
     @param argc [argument count]
     @param argv [argument vector]
     */
    SudokuQueueScheme(int argc, char** argv): board(BSIZE) {
        #pragma omp parallel
        {
            #pragma omp single
            {
                n_thread = omp_get_num_threads(); 
                std::cout << "Sudoku OMP started with " << n_thread << " threads"  << std::endl << std::endl;
            }
        }
    }

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
