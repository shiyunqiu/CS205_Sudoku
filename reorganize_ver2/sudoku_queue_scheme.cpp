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


int SudokuQueueScheme::THREAD_NUM = 2;
int SudokuQueueScheme::BOOTSTRAP_NUM = 8;


SudokuQueueScheme::SudokuQueueScheme() {

    omp_set_dynamic(0);
    omp_set_num_threads(THREAD_NUM);
    n_thread = omp_get_num_threads();

    std::cout << "OMP Number of Threads: ";
    std::cout << n_thread << std::endl;
}

void SudokuQueueScheme::task_begin() { 

    Board board(BSIZE); 
    read(board); 
    problems.push_back(board);

    std::cout << "Problem Board: " << std::endl;
    board.output(std::cout);
}

void SudokuQueueScheme::task_assign() {

    int minlen = BOOTSTRAP_NUM;
    if (minlen < 0) {
        minlen = 2 * n_thread * n_thread;
    }

    while (problems.size() > 0 && 
            problems.size() < minlen) {
        problems.bootstrap();
    }
    problems.solutions().dump(solutions);

    int N = problems.size();
    solvers.resize(N);

    std::cout << "Queue Length: " << N << std::endl;
}

void SudokuQueueScheme::task_process() {

    int N = problems.size();
    #pragma omp parallel for \
            schedule(dynamic) \
            shared(N, solvers, problems)
    for (int i = 0; i < N; i++) {
        solvers[i].solve(problems[i]);
    }
}

void SudokuQueueScheme::task_collect() {

    int N = problems.size();
    for (int i = 0; i < N; i++) {
        solvers[i].dump(solutions);
    }
}

void SudokuQueueScheme::task_end() {

    write(solutions); 
    std::cout << "Solution Board(s): " << std::endl;
    solutions.output(std::cout);
}

void SudokuQueueScheme::timer_start() {

    t_start = omp_get_wtime();
}

void SudokuQueueScheme::timer_stop() {

    t_stop = omp_get_wtime();
    std::cout << "Elapsed in ";
    std::cout << t_stop-t_start << " ";
    std::cout << "seconds (OMP WALL)" << std::endl << std::endl;
}