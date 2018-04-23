#include <iostream>
#include <deque>
#include <vector>
#include <mpi.h>
#include "board.hpp"
#include "board_deque.hpp"
#include "solver.hpp"
#include "bootstrapper.hpp"
#include "sudoku.hpp"
#include "sudoku_mpi.hpp"


int SudokuMPI::BOOTSTRAP_NUM_1 = 8;
int SudokuMPI::BOOTSTRAP_NUM_2 = 16;


void SudokuMPI::task_begin() {

    if (mpi_rank == 0) {

        Board board(BSIZE);
        read(board); 
        probs.push_back(board);

        std::cout << "Problem Board" << std::endl;
        board.output(std::cout);
    }
}



void SudokuMPI::task_assign() {

    if (mpi_rank == 0) {

        while (probs.size() > 0 && 
                probs.size() < BOOTSTRAP_NUM_1) {
            probs.bootstrap();
        }
        probs.solutions().dump(sols);

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "task queue of " << probs.size() << " boards bootstrapped" << std::endl;

        int n = probs.size();
        int nper = n / mpi_size;
        while (n >= 2 * nper) {
            schedule.push_back(nper); 
            n -= nper;
        }
        schedule.push_back(n); // the largest chunk is at the back of it

        int nloc;
        for (int r = 1; r < mpi_size; r++) {
            nloc = schedule.back();
            SMPI_DumpDeque(probs, r, nloc);
            schedule.pop_back();
        }

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << probs.size() << " boards kept" << std::endl;
    }
    else {

        SMPI_LoadDeque(probs, 0);

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << probs.size() << " boards assigned" << std::endl;
    }
}


void SudokuMPI::task_process() {

    while (probs.size() > 0 && 
            probs.size() < BOOTSTRAP_NUM_2) {
        probs.bootstrap();
    }
    probs.solutions().dump(sols);

    std::cout << "RANK-" << mpi_rank << ": ";
    std::cout << "sub queue augmented to " << probs.size() << " boards" << std::endl; 
    
    int N = probs.size();
    std::vector<Solver> solvers(N);

    #pragma omp parallel for \
            schedule(dynamic) \
            shared(N, probs, solvers)
    for (int i = 0; i < N; i++) {
        solvers[i].solve(probs[i]);
    }

    for (int i = 0; i < N; i++) {
        solvers[i].dump(sols);
    }

    std::cout << "RANK-" << mpi_rank << ": "; 
    std::cout << sols.size() << " solutions found" << std::endl;
}



void SudokuMPI::task_collect() {

    if (mpi_rank != 0){
        SMPI_DumpDeque(sols, 0, -1);
    }
    else {
        for (int r = 1; r < mpi_size; r++){
            SMPI_LoadDeque(sols, r);
        }

        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "results collected" << std::endl;
    }
}


void SudokuMPI::task_end() {

    if (mpi_rank == 0) {

        write(sols);
        std::cout << "Solution Board(s)" << std::endl;
        sols.output(std::cout);    
    }
}


void SudokuMPI::timer_start() {
    t_start = MPI_Wtime();
}

void SudokuMPI::timer_stop() {
    t_stop = MPI_Wtime();
    if (mpi_rank == 0) {
        std::cout << "RANK-" << mpi_rank << ": "; 
        std::cout << "Elapsed in " << t_stop - t_start << " ";
        std::cout << "seconds (MPI)" << std::endl << std::endl;
    }
}

void SudokuMPI::SMPI_DumpDeque(BoardDeque& bdeque, int r, int len) {

    if (len < 0) {
        len = bdeque.size();
    }

    MPI_Send(&len, 1, MPI_INT, 
             r, 50, MPI_COMM_WORLD);

    for (int i = 0; i < len; i++) {
        Board& b = bdeque.front();
        SMPI_SendBoard(b, r);
        bdeque.pop_front();
    }
}


void SudokuMPI::SMPI_LoadDeque(BoardDeque& bdeque, int r) {

    int len;
    MPI_Recv(&len, 1, MPI_INT, 
             r, 50, MPI_COMM_WORLD, &mpi_state);

    for (int i = 0; i < len; i++) {
        Board b(BSIZE);
        SMPI_RecvBoard(b, r);
        bdeque.push_back(b);
    }
}


void SudokuMPI::SMPI_SendBoard(Board& b, int r) {

    MPI_Send(b.as_array(), 
             BSIZE * BSIZE, MPI_INT, 
             r, 50, MPI_COMM_WORLD);
}


void SudokuMPI::SMPI_RecvBoard(Board& b, int r) {

    MPI_Recv(b.as_array(), 
             BSIZE * BSIZE, MPI_INT, 
             r, 50, MPI_COMM_WORLD, &mpi_state);
}


