/**
 @file faker.hpp
 @brief Header file for the Faker class
 @author Yiqi Xie, Shiyun Qiu, Yuyue Wang, Xiangru Shu
 @date May 3, 2018
 */


#ifndef FAKER_H
#define FAKER_H

#include "board.hpp"
#include "board_deque.hpp"

/*
 A fake sudoku generator based on permutation
 does not essentially generate new problems
 works for solvers that search in fixed order
*/

class Faker: public BoardDeque {
public:
    Faker(): BoardDeque() {}
    Faker(const Board& b): BoardDeque(b) {}
    void fake(const Board& b, unsigned seed=std::time(0));
    void fake(const Board& b, int n, unsigned seed=std::time(0)) {
        for (int i = 0; i < n; i++) {
            fake(b, seed++);
        }
    }
    void fake(int n=1, unsigned seed=std::time(0)) {
        fake(front(), n, seed);
        pop_front();
    }
protected:
    void permute_row(Board& bperm, std::vector<int> vperm, int rblock);
    void permute_col(Board& bperm, std::vector<int> vperm, int cblock);
    void permute_blockrow(Board& bperm, std::vector<int> vperm);
    void permute_blockcol(Board& bperm, std::vector<int> vperm);
};

#endif