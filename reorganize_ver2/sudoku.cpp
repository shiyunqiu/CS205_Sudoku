#include <iostream>
#include <fstream>
#include "board.hpp"
#include "board_deque.hpp"
#include "sudoku.hpp"


int Sudoku::BSIZE = 9;
std::string Sudoku::IFILE_NAME = "./problem.sdk";
std::string Sudoku::OFILE_NAME = "./solutions.txt";


void Sudoku::read(Board& b) {
    std::ifstream file(IFILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Error opening file ";
        std::cerr << IFILE_NAME << std::endl;
        exit(1);
    }
    b.input(file);
}

void Sudoku::write(BoardDeque& bq) {
    std::ofstream file(OFILE_NAME);
    if (!file.is_open()) {
        std::cerr << "Error opening file ";
        std::cerr << IFILE_NAME << std::endl;
        exit(1);
    }
    bq.output(file);
}