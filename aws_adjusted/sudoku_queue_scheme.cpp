/**
 @file sudoku_queue_scheme.cpp
 @brief Implementation for queue construction
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Construct a queue of boards to be used in the OpenMP version and MPI version of the solver.
 */
#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku.hpp"
#include "sudoku_queue_scheme.hpp"

// number of threads
int SudokuQueueScheme::THREAD_NUM = 2;
// number of bootstrapping
int SudokuQueueScheme::BOOTSTRAP_NUM = 8;

/* Constructor of class SudokuQueueScheme: set the number of threads for the OpenMP version. */
SudokuQueueScheme::SudokuQueueScheme() {

    // omp_set_dynamic(0);
    // omp_set_num_threads(THREAD_NUM);
    // n_thread = omp_get_num_threads();

    // std::cout << "OMP Number of Threads: ";
    // std::cout << n_thread << std::endl;
}

/* Read the content of a puzzle file, push the problem to a deque, and output the board. */
void SudokuQueueScheme::task_begin() { 

    // Board board(BSIZE); 
    // read(board); 
    // problems.push_back(board);

    // std::cout << "Problem Board: " << std::endl;
    // board.output(std::cout);
}

/* Bootstrapping: generate N (determined by BOOTSTRAP_NUM and the bootstrap function) potential boards and push them into a deque to be solved in parallel. */
void SudokuQueueScheme::task_assign() {

    // int minlen = BOOTSTRAP_NUM;
    // // if given a negative number, ensure some level of bootstrapping
    // if (minlen < 0) {
    //     minlen = 2 * n_thread * n_thread;
    // }

    // while (problems.size() > 0 && 
    //         problems.size() < minlen) {
    //     problems.bootstrap();
    // }
    // // push into a deque
    // problems.solutions().dump(solutions);

    // int N = problems.size();
    // solvers.resize(N);

    // std::cout << "Queue Length: " << N << std::endl;
}

/* Solve the problem in parallel using OpenMP. */
void SudokuQueueScheme::task_process() {

    omp_set_dynamic(0);
    // omp_set_num_threads(THREAD_NUM);
    n_thread = omp_get_num_threads();

    std::cout << "OMP Number of Threads: ";
    std::cout << n_thread << std::endl;

    Board board(BSIZE); 
    read(board); 
    Bootstrapper problems(board);

    std::cout << "Problem Board: " << std::endl;
    board.output(std::cout);

    int minlen = BOOTSTRAP_NUM;
    // if given a negative number, ensure some level of bootstrapping
    if (minlen < 0) {
        minlen = 2 * n_thread * n_thread;
    }
    while (problems.size() > 0 && 
            problems.size() < minlen) {
        problems.bootstrap();
    }
    // push into a deque
    problems.solutions().dump(solutions);

    int N = problems.size();
    std::vector<Solver> solvers(N);
    std::cout << "Queue Length: " << N << std::endl;

    #pragma omp parallel for \
            schedule(dynamic) \
            shared(N, solvers, problems)
    for (int i = 0; i < N; i++) {
        solvers[i].solve(problems[i]);
    }

    for (int i = 0; i < N; i++) {
        solvers[i].dump(solutions);
    }

    // write(solutions); 
    // std::cout << "Solution Board(s): " << std::endl;
    // solutions.output(std::cout);
}

/* Collect the solutions found by all threads. */
void SudokuQueueScheme::task_collect() {

    // int N = problems.size();
    // for (int i = 0; i < N; i++) {
    //     solvers[i].dump(solutions);
    // }
}

/* Write the solutions into a file, and print out the solution boards. */
void SudokuQueueScheme::task_end() {

    write(solutions); 
    std::cout << "Solution Board(s): " << std::endl;
    solutions.output(std::cout);
}

/* Start of the OpenMP timer. */
void SudokuQueueScheme::timer_start() {

    t_start = omp_get_wtime();
}

/* End of the OpenMP timer and show elapsed time of execution. */
void SudokuQueueScheme::timer_stop() {

    t_stop = omp_get_wtime();
    std::cout << "Elapsed in ";
    std::cout << t_stop-t_start << " ";
    std::cout << "seconds (OMP WALL)" << std::endl << std::endl;
}
