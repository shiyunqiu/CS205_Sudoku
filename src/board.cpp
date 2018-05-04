/**
 @file board.cpp
 @brief Record a board by an array
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date April 19, 2018
 
 Construct a queue of boards to be used in the OpenMP version and MPI version of the solver.
 */
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include "board.hpp"

/** Default constructor of class Board: assign size as 0 and array as NULL */
Board::Board(): 
size(0), array(NULL) {}

/** Constructor of class Board: save the size of the board and construct a sizexsize array
 @param bsize [row size of the board]
 */
Board::Board(int bsize): 
size(bsize) { 
    array = new int[size*size]; 
}

/** Copy constructor of class Board: save the size of the board and construct a sizexsize array by copying barray
 @param bsize [row size of the board]
 @param barray [another array containing a board]
 */
Board::Board(int bsize, const int* barray): 
size(bsize) { 
    array = new int[size*size];
    std::memcpy(array, barray, size*size*sizeof(int)); }

/** Copy constructor of class Board: save the size of the board and construct a sizexsize array by copying board b
 @param b [a board]
 */
Board::Board(const Board& b): 
size(b.size) { 
    array = new int[size*size]; 
    std::memcpy(array, b.array, size*size*sizeof(int));
}

/** Destructor: deleting the array and free the memory. */
Board::~Board() { delete [] array; }

/** Get the number of a cell.
 @param i [row index]
 @param j [column index]
 @return the number at position i, j on the board
 */
int& Board::cell(int i, int j) { return array[i * size + j]; }

/** Get the number in position i of the array.
 @param i [position in the array]
 @return [the number in position i of the array]
 */
int* Board::operator[] (int i) { return array + i * size; }

/** Get the protected parameter array
 @return array [protected variable array containing all information of a board]
 */
int* Board::as_array() { return array; }

/** Get the protected parameter size
 @return size [row size of the board]
 */
int Board::get_size() const { return size; }

/** Get the total number of cells of the board
 @return [total number of cells of the board]
 */
int Board::get_ncell() const { return size * size; };

/** Calculate the total number of empty cells on the board
 @return n [total number of empty cells]
 */
int Board::get_nempty() const {
    int n = 0;
    for (int i = 0; i < get_ncell(); i++) {
        n += (array[i] == 0);
    }
    return n;
};

/** Check if number n can be put at position (row, col)
 @param row [row index]
 @param col [column index]
 @param n [number to be checked]
 @return true/false [whether a number n can be put at position (row, col)]
 */
bool Board::safe(int row, int col, int n) const {

    int r, c, br, bc;
    int blocksize = sqrt(size);
    // same value already in the cell
    if (array[row * size + col] == n) return true;
    // some other value already in the cell
    if (array[row * size + col] != 0) return false;
    // value exists in the row
    for (c = 0; c < size; c++)
        if (array[row * size + c] == n) return false;
    // value exists in the column
    for (r = 0; r < size; r++)
        if (array[r * size + col] == n) return false;
    // value exists in the block
    br = row / blocksize;
    bc = col / blocksize;
    for (r = br * blocksize; r < (br + 1) * blocksize; r++)
        for (c = bc * blocksize; c < (bc + 1) * blocksize; c++)
            if (array[r * size + c] == n) return false;
    return true;

}

/** Load a Sudoku board from a file into an array
 @param in [the stream to get data from]
 */
void Board::input(std::istream& in) {
    int index = 0, i = 0, j = 0;
    std::string line;
    while (index < get_ncell() && 
            std::getline(in, line)) {
        std::istringstream ss(line);
        while (index < get_ncell() && 
                ss >> array[index]) {
            index++;
            i = index / size;
            j = index % size;
        }
    }
    if (index < get_ncell() - 1) {
        printf("row %d, col %d\n", i, j);
        std::cerr << "Error: malformed input" << std::endl;
        exit(1);
    }
}

/** Write an array to a file/console, output like a board
 @param out [the stream to output data to]
 */
void Board::output(std::ostream& out) const {

    int r, c;
    int blocksize = sqrt(size);
    int digit = int(log10(size)) + 1;

    out << std::endl;
    for (r = 0; r < size; r++) {
        for (c = 0; c < size; c++) {
            out << std::setw(digit) << array[r * size + c] << " ";
            if (c % blocksize == (blocksize-1)) out << "  ";
        }
        out << std::endl;
        if (r % blocksize == (blocksize-1)) out << std::endl;
    }

}
