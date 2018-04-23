#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
// #include "sudoku_mpi.hpp"
// #include <omp.h>

void read(Board& b, const std::string& fname);
void write(BoardDeque& bdeque, const std::string& fname);

void serial_solve(Board& sudoku, BoardDeque& sols);
void serial_bootstrap(Board& sudoku, BoardDeque& sols);
void queue_scheme(Board& sudoku, BoardDeque& sols, int n_thread=2);
void stack_scheme(Board& sudoku, BoardDeque& sols, int n_thread=2);
void mpi(int bsize, const std::string& filename, int argc, char** argv);


int main(int argc, char** argv) {

    int bsize = 9;
    std::string filename = "../../test_cases/test9.sdk";
    
    // SudokuMPI::BOOTSTRAP_N1 = 8;
    // SudokuMPI::BOOTSTRAP_N2 = 16;
    // mpi(bsize, filename, argc, argv);

    Board sudoku(bsize);
    read(sudoku, filename);
    std::cout << "Problem Board: " << std::endl;
    sudoku.output();

    clock_t tic = clock();
    BoardDeque sols;
    serial_solve(sudoku, sols);
    // serial_bootstrap(sudoku, sols);
    // queue_scheme(sudoku, sols, 2);
    // stack_scheme(sudoku, sols, 2);
    clock_t toc = clock();

    std::cout << "Elapsed in " << double(toc-tic)/CLOCKS_PER_SEC << " seconds (CPU)" << std::endl << std::endl;
    std::cout << "Solution Board(s): " << std::endl;

    sols.output();
    
    std::string outfname = "./solutions.txt";
    write(sols, outfname);

    return 0;
}


// void mpi(int bsize, const std::string& filename, int argc, char** argv) {
//     SudokuMPI smpi(bsize, &argc, &argv);
//     smpi.task_begin(filename);
//     smpi.task_assign();
//     smpi.task_process();
//     smpi.task_collect();
//     smpi.task_end(std::cout);
// }


void serial_solve(Board& sudoku, BoardDeque& sols) {

    Solver solver(sudoku);
    solver.solve();
    solver.dump(sols);
}



void serial_bootstrap(Board& sudoku, BoardDeque& sols) {

    Bootstrapper boot(sudoku);
    while (boot.size() > 0) {
        boot.bootstrap();
    }
    boot.solutions().dump(sols);
}


void queue_scheme(Board& sudoku, BoardDeque& sols, int n_thread) {

    // omp_set_dynamic(0);
    // omp_set_num_threads(n_thread);
    // std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;
    // double tic = omp_get_wtime();

    Bootstrapper boot(sudoku); // the queue (front=front, back=back)

    int minlen = 2 * n_thread * n_thread;
    while (boot.size() < minlen && boot.size() > 0) {
        boot.bootstrap();
    }
    boot.solutions().dump(sols);

    int N = boot.size();
    std::vector<Solver> SOLVERS(N);

    std::cout << "Queue Length: " << N << std::endl;

    /* parallelize */
    #pragma omp parallel for schedule(dynamic) shared(N, SOLVERS, boot)
    for (int i = 0; i < N; i++) {
        SOLVERS[i].solve(boot[i]);
    }

    /* collect */
    for (int i = 0; i < N; i++) {
        SOLVERS[i].dump(sols);
    }

    // double toc = omp_get_wtime();
    // std::cout << "Elapsed in " << toc-tic << " seconds (OMP)" << std::endl;

}


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


void read(Board& b, const std::string& fname) {
    std::ifstream file(fname);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << fname << std::endl;
        exit(1);
    } else {
        b.input(file);
    }
    file.close();
}

void write(BoardDeque& bdeque, const std::string& fname) {
    std::ofstream file(fname);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << fname << std::endl;
        exit(1);
    } else {
        bdeque.output(file);
    }
    file.close();
}