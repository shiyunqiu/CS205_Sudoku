#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "board.h"


Board::Board(): 
size(0), array(NULL) {}

Board::Board(int bsize): 
size(bsize) { 
    array = new int[size*size]; 
}

Board::Board(int bsize, const int* barray): 
size(bsize) { 
    array = new int[size*size];
    std::memcpy(array, barray, size*size*sizeof(int)); }

Board::Board(const Board& b): 
size(b.size) { 
    array = new int[size*size]; 
    std::memcpy(array, b.array, size*size*sizeof(int));
}

Board::Board(int bsize, const std::string& filename): 
size(bsize) { 
    array = new int[size*size]; 
    load(filename); 
}

Board::~Board() { delete [] array; }

int& Board::cell(int i, int j) { return array[i * size + j]; }

int* Board::operator[] (int i) { return array + i * size; }

int* Board::as_array() { return array; }

int Board::get_size() const { return size; }

int Board::get_ncell() const { return size * size; };

int Board::get_nempty() const {
    int n = 0;
    for (int i = 0; i < get_ncell(); i++) {
        n += (array[i] == 0);
    }
    return n;
};

void Board::load(const std::string& filename) {
    std::ifstream file(filename);
    // if no file exists, error message
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    } else {
        std::string line;
        int i = 0;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            int j = 0;
            while (ss >> array[i * size + j]) {
                if (j < size) {
                    j++;
                }
                else { 
                    j = 0;
                    i++;
                }
            }
            // grid size of the board in the file not matching the given grid size
            if (++i > size || j > size) {
                printf("%d %d\n", i, j);
                std::cerr << "Error: malformed file" << std::endl;
                exit(1);
            }
        }
    }
}

void Board::output(std::ostream& out) const {

    int r, c;
    int blocksize = sqrt(size);

    out << std::endl;
    for (r = 0; r < size; r++) {
        for (c = 0; c < size; c++) {
            out << array[r * size + c] << " ";
            if (c % blocksize == (blocksize-1)) out << "  ";
        }
        out << std::endl;
        if (r % blocksize == (blocksize-1)) out << std::endl;
    }

}

bool Board::safe(int row, int col, int n) const {

    int r, c, br, bc;
    int blocksize = sqrt(size);
    if (array[row * size + col] == n) return true;
    if (array[row * size + col] != 0) return false;
    for (c = 0; c < size; c++)
        if (array[row * size + c] == n) return false;
    for (r = 0; r < size; r++)
        if (array[r * size + col] == n) return false;
    br = row / blocksize;
    bc = col / blocksize;
    for (r = br * blocksize; r < (br + 1) * blocksize; r++)
        for (c = bc * blocksize; c < (bc + 1) * blocksize; c++)
            if (array[r * size + c] == n) return false;
    return true;

}
