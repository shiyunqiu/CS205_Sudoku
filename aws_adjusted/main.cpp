/**
 @file main.cpp
 @brief Giant Sudoku Solver
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 This is a solver for Sudoku problems of any size. Serial, OpenMP, and MPI+OpenMP versions are available. A brutal force solver is implemented in the serial version. For the parallel version, we generate n potential boards by bootstrapping and push all the boards into a dequeue. OpenMP enables all threads to solve the Sudoku puzzle simultaneously while MPI makes sure that all nodes are solveing the problem in parallel.
 */
#include <iostream>
#include <vector>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku.hpp"
#include "sudoku_serial.hpp"
#include "sudoku_queue_scheme.hpp"
#include "sudoku_mpi.hpp"


void demo(); // read this for quick start


int main(int argc, char** argv) {

    Sudoku::BSIZE = 16;
    Sudoku::IFILE_NAME = "../test_cases/test16_1min.sdk";
    Sudoku::OFILE_NAME = "./solutions.txt";

    // SudokuSerial sudoku(argc, argv); 

    // SudokuQueueScheme::THREAD_NUM = 4;
    // SudokuQueueScheme::BOOTSTRAP_NUM = 128;
    // SudokuQueueScheme sudoku(argc, argv);

    SudokuMPI::BOOTSTRAP_NUM_1 = 16;
    SudokuMPI::BOOTSTRAP_NUM_2 = 32;
    SudokuMPI sudoku(argc, argv);

    sudoku.run();

    // demo();

    return 0;
}


void demo() {

    // general settings
    Sudoku::BSIZE = 9;  // board size
    Sudoku::IFILE_NAME = "./test9.sdk";     // input path
    Sudoku::OFILE_NAME = "./solutions.txt"; // output path

    // initialize
    Board problem(Sudoku::BSIZE);
    Sudoku::read(problem); // read from file
    std::cout << "Problem Board: " << std::endl;
    problem.output(std::cout);

    // solve
    BoardDeque solutions;
    Solver solver;
    solver.solve(problem);
    solver.dump(solutions);

    // output
    Sudoku::write(solutions); // write to file
    std::cout << "Solution Board(s): " << std::endl;
    solutions.output(std::cout);
}



// void serial_bootstrap(Board& sudoku, BoardDeque& sols) {

//     Bootstrapper boot(sudoku);
//     while (boot.size() > 0) {
//         boot.bootstrap();
//     }
//     boot.solutions().dump(sols);
// }


// void stack_scheme(Board& sudoku, int n_thread) {

//     // omp_set_dynamic(0);
//     // omp_set_num_threads(n_thread);
//     // std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;

//     BoardDeque probs(sudoku); // the stack (top=back)
//     BoardDeque sols;

//     // double tic = omp_get_wtime();

//     int N = 2 * n_thread * n_thread;
//     std::vector<Bootstrapper> BOOTS(N);
//     std::cout << "Number of Bootstrappers: " << N << std::endl;

//     while (probs.size() > 0) {

//         for (int i = 0; i < N; i++) {
//             probs.passBB(BOOTS[i]);
//             if (probs.size() <= 0) break;
//         }
//         #pragma omp parallel for schedule(dynamic) shared(N, BOOTS)
//         for (int i = 0; i < N; i++) {
//             BOOTS[i].bootstrap();
//         }

//         // for (int i = 0; i < N; i++) {
//         //     BOOTS[i].dump(probs);
//         // }
//     }

//     for (int i = 0; i < N; i++) {
//         BOOTS[i].solutions().dump(sols);  
//     }

//     sols.output();

//     // std::cout << "Elapsed in " << toc-tic << " seconds" << std::endl;

// }
