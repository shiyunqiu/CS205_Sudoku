/**
 @file board.h
 @author Yiqi Xie
 @date April 20, 2018
 */

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <deque>

class Board {
/* 
    A board for sudoku, based on 1d int array.

    Main features:
     - 2d array access:         board[i][j], board.cell(i,j)
     - input from std::istream: board.input(std::cin)
     - output to std::ostream:  board.output(std::cout)
     - proposal check:          board.safe(i, j, n)
     
 */
public:
    Board();
    Board(int bsize);
    Board(int bsize, const int* barray);
    Board(const Board& b);
    void input(std::istream& in=std::cin);
    void output(std::ostream& out=std::cout) const;
    int get_size() const;
    int get_ncell() const;
    int get_nempty() const;
    int* as_array();
    int* operator[] (int i);
    int& cell(int i, int j);
    bool safe(int row, int col, int n) const;
    ~Board();
protected:
    int size;
    int* array;
};

#endif