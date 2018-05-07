/**
 @file sudoku_queue_scheme.cpp
 @brief Implementation for queue construction
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Construct a queue of boards to be used in the OpenMP version and MPI version of the solver.
 */
#include <iostream>
#include <vector>
#include <omp.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku_queue_scheme.hpp"

// The following parameters should be set in main.cpp
// number of bootstrapping
int SudokuQueueScheme::BOOTSTRAP_NUM = 8;

/** Read the content of a puzzle file, push the problem to a deque, and output the board. */
void SudokuQueueScheme::task_begin() { 

    read(board);
    std::cout << "Problem Board: " << std::endl;
    board.output(std::cout);
}

/** Solve the problem in parallel using OpenMP. */
void SudokuQueueScheme::task_process() {

    Bootstrapper problems(board);

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
}

/** Write the solutions into a file, and print out the solution boards. */
void SudokuQueueScheme::task_end() {

    write(solutions);
    std::cout << "Solution Board(s): " << std::endl;
    solutions.output(std::cout);
}

/** Start of the OpenMP timer. */
void SudokuQueueScheme::timer_start() {

    t_start = omp_get_wtime();
}

/** End of the OpenMP timer and show elapsed time of execution. */
void SudokuQueueScheme::timer_stop() {

    t_stop = omp_get_wtime();
    std::cout << "Elapsed in ";
    std::cout << t_stop-t_start << " ";
    std::cout << "seconds (OMP WALL)" << std::endl << std::endl;
}
