#include <iostream>
#include <ctime>
#include "board.h"
#include "board_queue.h"
#include "board_stack.h"
#include "solver.h"
#include "bootstrapper.h"
// #include <omp.h>


void serial_depthfirst(Board& sudoku);
void serial_breadthfirst_queue(Board& sudoku);
void serial_breadthfirst_stack(Board& sudoku);
void parallel_omp_queue(Board& sudoku, int n_thread=2);
void parallel_omp_stack(Board& sudoku, int n_thread=2);


int main(int argc, char** argv) {

    int bsize = 9;
    std::string filename ="/Users/shell/Documents/Projects/cs205_final/test_cases/test9.sdk";

    std::cout << "Problem Board: " << std::endl;
    Board sudoku(bsize, filename);
    sudoku.output();

    serial_depthfirst(sudoku);
    // serial_breadthfirst_queue(sudoku);
    // serial_breadthfirst_stack(sudoku);
    // parallel_omp_queue(sudoku, 2);
    // parallel_omp_stack(sudoku, 2);

    return 0;
}


void serial_depthfirst(Board& sudoku) {

    BoardQueue solutions;
    Solver solver;

    clock_t tic = clock();
    solver.solve(sudoku, solutions);
    clock_t toc = clock();

    std::cout << "Solution Board(s):" << std::endl;
    solutions.output();

    std::cout << "Elapsed in " << double(toc-tic)/CLOCKS_PER_SEC << " seconds" << std::endl;
}



void serial_breadthfirst_queue(Board& sudoku) {

    BoardQueue problems(sudoku), solutions;
    Bootstrapper bootstrapper;

    clock_t tic = clock();
    while (problems.size() > 0) {
        if (bootstrapper.bootstrap(problems)) {
            // problems.output(); break;
            problems.pass(solutions);
        }
    }
    clock_t toc = clock();

    std::cout << "Solution Board(s):" << std::endl;
    solutions.output();

    std::cout << "Elapsed in " << double(toc-tic)/CLOCKS_PER_SEC << " seconds" << std::endl;
}



void serial_breadthfirst_stack(Board& sudoku) {

    BoardStack problems(sudoku), solutions;
    Bootstrapper bootstrapper;

    clock_t tic = clock();
    while (problems.size() > 0) {
        if (bootstrapper.bootstrap(problems)) {
            problems.output(); break;
            // problems.pass(solutions);
        }
    }
    clock_t toc = clock();

    std::cout << "Solution Board(s):" << std::endl;
    solutions.output();

    std::cout << "Elapsed in " << double(toc-tic)/CLOCKS_PER_SEC << " seconds" << std::endl;
}


void parallel_omp_queue(Board& sudoku, int n_thread) {

    // omp_set_dynamic(0);
    // omp_set_num_threads(n_thread);
    // std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;

    BoardQueue problems(sudoku), solutions;
    Bootstrapper bootstrapper;
    Solver solver;

    // double tic = omp_get_wtime();

    int n_bootstrap = n_thread * n_thread;
    while (problems.size() < n_bootstrap && problems.size() > 0) {
        if (bootstrapper.bootstrap(problems)) {
            // problems.output(); break;
            problems.pass(solutions);
        }
    }

    std::cout << "Queue size: " << problems.size() << std::endl;
    // problems.output();

    // int N = problems.size();
    // #pragma omp parallel for schedule(dynamic) shared(N, problems, solutions) private(solver)
    // for (int i = 0; i < N; i++) {
    //     solver.solve(problems[i], solutions);
    // }

    // double toc = omp_get_wtime();

    solutions.output();

    // std::cout << "Elapsed in " << toc-tic << " seconds" << std::endl;

}