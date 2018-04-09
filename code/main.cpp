//
//  main.cpp
//  Sudoku
//
//  Created by Shiyun Qiu on 4/8/18.
//  Copyright © 2018 Shiyun Qiu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "Sudoku_serial.hpp"

int main(int argc, const char * argv[]) {
    int len = 16;
    clock_t begin = clock();
    SudokuSerial ss("/Users/shiyunqiu/Documents/Spring 2018/CS 205/Final Project/Sudoku/test16_2.sdk", len);
    ss.solve(0, 0);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << " seconds.\n";
    return 0;
}
