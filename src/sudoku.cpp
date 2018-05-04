/**
 @file sudoku.cpp
 @brief Implementation for base class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 */
#include <iostream>
#include <fstream>
#include "sudoku.hpp"

// the following three parameters should be changed in the main.cpp
// default grid size (row length) of the Sudoku puzzle
int Sudoku::BSIZE = 9;
// default input filename
std::string Sudoku::IFILE_NAME = "./problem.sdk";
// default output filename
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
