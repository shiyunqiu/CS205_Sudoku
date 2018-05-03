#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "faker.hpp"


void Faker::fake(const Board& b, unsigned seed) {

    push_back(b);
    Board& bperm = back();

    int bsize = bperm.get_size();
    int nblock = sqrt(bsize);

    std::vector<int> vperm(nblock);
    for (int i = 0; i < nblock; i++) vperm[i] = i;

    std::default_random_engine random_generator(seed);

    for (int rblock = 0; rblock < nblock; rblock++) {
        std::shuffle(vperm.begin(), vperm.end(), random_generator);
        permute_row(bperm, vperm, rblock);
    }

    for (int cblock = 0; cblock < nblock; cblock++) {
        std::shuffle(vperm.begin(), vperm.end(), random_generator);
        permute_col(bperm, vperm, cblock);
    }

    std::shuffle(vperm.begin(), vperm.end(), random_generator);
    permute_blockrow(bperm, vperm);

    std::shuffle(vperm.begin(), vperm.end(), random_generator);
    permute_blockcol(bperm, vperm);
}


void Faker::permute_row(Board& bperm, std::vector<int> vperm, int rblock) {

    int bsize = bperm.get_size();
    int nblock = sqrt(bsize);

    int* tarray = new int[nblock*bsize];

    for (int i = 0; i < nblock; i++) {
        for (int j = 0; j < bsize; j++) {
            tarray[i*bsize+j] = bperm[rblock*nblock+i][j];
        }
    }

    for (int i = 0; i < nblock; i++) {
        for (int j = 0; j < bsize; j++) {
            bperm[rblock*nblock+i][j] = tarray[vperm[i]*bsize+j];
        }
    }

    delete [] tarray;
}

void Faker::permute_col(Board& bperm, std::vector<int> vperm, int cblock) {

    int bsize = bperm.get_size();
    int nblock = sqrt(bsize);

    int* tarray = new int[nblock*bsize];

    for (int i = 0; i < bsize; i++) {
        for (int j = 0; j < nblock; j++) {
            tarray[i*nblock+j] = bperm[i][cblock*nblock+j];
        }
    }

    for (int i = 0; i < bsize; i++) {
        for (int j = 0; j < nblock; j++) {
            bperm[i][cblock*nblock+j] = tarray[i*nblock+vperm[j]];
        }
    }

    delete [] tarray;
}

void Faker::permute_blockrow(Board& bperm, std::vector<int> vperm) {

    int bsize = bperm.get_size();
    int nblock = sqrt(bsize);

    Board btmp(bperm);

    for (int i = 0; i < nblock; i++) {
        for (int j = 0; j < nblock; j++) {
            for (int k = 0; k < bsize; k++){
                bperm[i*nblock+j][k] = btmp[vperm[i]*nblock+j][k];
            }
        }
    }
}

void Faker::permute_blockcol(Board& bperm, std::vector<int> vperm) {

    int bsize = bperm.get_size();
    int nblock = sqrt(bsize);

    Board btmp(bperm);

    for (int i = 0; i < nblock; i++) {
        for (int j = 0; j < nblock; j++) {
            for (int k = 0; k < bsize; k++){
                bperm[k][i*nblock+j] = btmp[k][vperm[i]*nblock+j];
            }
        }
    }
}



