/**
 @file sudoku.cpp
 @brief Implementation for base class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */
#include <iostream>
#include <fstream>
#include "board.hpp"
#include "board_deque.hpp"
#include "sudoku.hpp"

// grid size (row length) of the Sudoku puzzle
int Sudoku::BSIZE = 9;
// input filename
std::string Sudoku::IFILE_NAME = "./problem.sdk";
// output filename
std::string Sudoku::OFILE_NAME = "./solutions.txt";

/** Read the content of the filename into a Sudoku puzzle board.
 @param b [Sudoku puzzle board]
 */
void Sudoku::read(Board& b) {
    std::ifstream file(IFILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Error opening file ";
        std::cerr << IFILE_NAME << std::endl;
        exit(1);
    }
    b.input(file);
}

/** Write the solutions of a Sudoku puzzle to a file.
 @param bq [Sudoku puzzle board]
 */
void Sudoku::write(BoardDeque& bq) {
    std::ofstream file(OFILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Error opening file ";
        std::cerr << IFILE_NAME << std::endl;
        exit(1);
    }
    bq.output(file);
}
