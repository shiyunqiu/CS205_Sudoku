//
//  Sudoku_parallel.cpp
//  Sudoku
//
//  Created by Yiqi Xie on 4/19/18.
//  Copyright © 2018 Yiqi Xie. All rights reserved.
//

#include <iostream>
#include "Sudoku_mpi.hpp"
#include "Sudoku_parallel.hpp"
#include "Sudoku_serial.hpp"
#include <vector>
#include <mpi.h>


int SudokuMPI::SMNGEN = 4;


/** Analyze the board to determine the amount of bootstrapping to do. */
void SudokuMPI::analyze()
{
    if (SMNGEN < 1) {
        // Count the number of zeros in the board
        int nz = 0;
        for (int i=0; i<grid_size; ++i){
            for (int j=0; j<grid_size; ++j){
                if (board[i][j]==0) nz++;
            }
        }
        // How to do this interpolation?
        ngen = 4+(4.-13.)/(53.-64.)*(nz-53);
    }
    else {
        ngen = SMNGEN;
    }
}


void SudokuMPI::solve(bool warm_start)
{

    int Ncell = grid_size * grid_size;

    /* MPI initialization*/

    int mpi_rank, mpi_size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Status mpi_state;

    double t_begin = MPI_Wtime();

    /* MPI-level task generation/assignment */

    int mpi_nloc;

    if (mpi_rank == 0) {

        std::cout << "Number of Processes: " << mpi_size << std::endl;

        /* task generation */
        if (!warm_start) {
            starts.emplace_back(SudokuSerial(*this)); // a deep copy
        }
        for (int i=0; i<ngen; ++i) generate();

        int mpi_n = starts.size();
        int mpi_nper = mpi_n / mpi_size;
        std::cout << "RANK-" << mpi_rank << " generated the MPI-level queue sized " << mpi_n << std::endl;

        for (int r = 1; r < mpi_size; r++) {

            /* send the number of boards in chunk */
            MPI_Send(&mpi_nper, 1, MPI_INT, r, 50, MPI_COMM_WORLD);

            /* send the chunk (and pop those sent) */
            int chunklen = mpi_nper * Ncell;
            int* chunkarray = new int[chunklen];
            for (int i = 0; i < mpi_nper; i++) {
                starts.front().to_array(chunkarray + i*Ncell);
                starts.pop_front();
            }
            MPI_Send(chunkarray, chunklen, MPI_INT, r, 50, MPI_COMM_WORLD);
            delete [] chunkarray;
        }
        mpi_nloc = starts.size();
        std::cout << "RANK-" << mpi_rank << " is left with a chunck of " << mpi_nloc << std::endl;

    }
    else {

        /* recover the number of boards in chunck */
        MPI_Recv(&mpi_nloc, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &mpi_state);

        /* recover the chunck */
        int chunklen = mpi_nloc * Ncell;
        int* chunkarray = new int[chunklen];
        MPI_Recv(chunkarray, chunklen, MPI_INT, 0, 50, MPI_COMM_WORLD, &mpi_state);
        for (int i = 0; i < mpi_nloc; i++) {
            SudokuSerial s(chunkarray + i*Ncell, grid_size);
            starts.push_back(s);
        }
        delete [] chunkarray;
        std::cout << "RANK-" << mpi_rank << " received a chunck of " << mpi_nloc << std::endl;

    }


    /* OMP-level solution */

    SudokuParallel::solve(true); // warm_start=true -> the board will not emplace itself back into the queue


    /* MPI-level result collection */

    int nsol = solutions.size();
    int* solarray = new int[Ncell];
    std::cout << "RANK-" << mpi_rank << " ended up with " << nsol << " solution(s)" << std::endl;

    if (mpi_rank != 0) {

        MPI_Send(&nsol, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);

        for (int i = 0; i < nsol; i++) {
            solutions.front().to_array(solarray);
            MPI_Send(solarray, Ncell, MPI_INT, 0, 50, MPI_COMM_WORLD);
            solutions.pop_front();
        }

    }
    else {

        int nsol_others;

        for (int r = 1; r < mpi_size; r++) {

            MPI_Recv(&nsol_others, 1, MPI_INT, r, 50, MPI_COMM_WORLD, &mpi_state);
            nsol += nsol_others;

            for (int i = 0; i < nsol_others; i++) {
                MPI_Recv(solarray, Ncell, MPI_INT, 0, 50, MPI_COMM_WORLD, &mpi_state);
                solutions.push_back(Sudoku(solarray, grid_size));
            }

        }

        double t_end = MPI_Wtime(); 
        std::cout << "RANK-" << mpi_rank << " has collected the results" << std::endl;

        for (int i = 0; i < nsol; i++) {
            std::cout << std::endl << "SOLUTION " << i+1 << std::endl << std::endl;
            solutions.front().output(std::cout);
            solutions.pop_front();
        }
        std::cout << "RANK-" << mpi_rank << " elapsed in " << t_end - t_begin << " seconds" << std::endl;

    }

    delete [] solarray;

    
    /* MPI finalization */

    MPI_Finalize();


}








