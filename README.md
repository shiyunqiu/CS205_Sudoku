# Parallelized Giant Sudoku Solver
Spring 2018 Harvard CS 205 Final Project

Group 1: Shiyun Qiu, Xiangru Shu, Yiqi Xie, Yuyue Wang

# Introduction

Sudoku is a combinatorial number placement puzzle. The objective of this game is to fill a 9×9 grid (board) with digits so that each column, each row, and each of the nine 3×3 subgrids (boxes) contains all of the digits from 1 to 9. Higher-rank sudokus usually have <a href="https://www.codecogs.com/eqnedit.php?latex=n^2*n^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n^2*n^2" title="n^2*n^2" /></a> board with <a href="https://www.codecogs.com/eqnedit.php?latex=n*n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n*n" title="n*n" /></a> boxes (n>3). However, higher-rank sudokus take hours to run in serial. Thus, we aim to parallelize a sudoku solver algorithm with several parallelization techniques (OpenMP and MPI), so that giant sudoku solver can be solved within a limited time.

# How-to-use

## Download Source Code

To run our sudoku solver, first download our [source code](https://github.com/shiyunqiu/CS205_Sudoku).

## Set Up

As our program requires OpenMP and MPI, we recommend using AWS to run our code. To set up OpenMP and MPI on AWS, we followed the guides provided by CS205: [OpenMP](https://canvas.harvard.edu/courses/37285/files/5490479?module_item_id=363501) and [MPI](https://canvas.harvard.edu/courses/37285/files/5490480?module_item_id=363500).

After connecting to the AWS instance, copy the source code and test cases from local to the AWS instance using the following command:

```
scp -i [key] [source code] [AWS Public IP]
```

For example, in our case, the command would be: 

```
scp -i ~/.ssh/cs205­key.pem code/* ubuntu@ec2­18­218­17­64.us­east­2.compute.amazonaws.com:
```

Then go back to the instance and do `sudo apt-get update`. You should make sure you have installed the following packages:

```
sudo apt-get install g++
```

```
sudo apt-get install build-essential
```

## Run

Then you should be able to run the program by use the following commands:

```
make
```

```
run
```

To run MPI version, after command `make`, copy file `run` to directory `cloud`, then go to `cloud` and use the following command to run:

```
 mpirun -np [number of nodes] -hosts master,node1... ./run
```

For example, to use 4 nodes, the command is:
```
 mpirun -np 4 -hosts master,node1,node2,node3,node4 ./run
```

## Test Cases

All the [test cases](https://github.com/shiyunqiu/CS205_Sudoku/tree/master/test_cases) are under the `test_cases` directory in our Github Repository. 

`test16_1min.sdk`: a 16 * 16 sudoku problem, took 1 min to solve in serial version

`test16_5min.sdk`: a 16 * 16 sudoku problem, took 5 min to solve in serial version 

`test16_15min.sdk`: a 25 * 25 sudoku problem, took 15 min to solve in serial version

`test25_5min.sdk`: a 25 * 25 sudoku problem, took 5 min to solve in serial version 

`test25_15min.sdk`: a 25 * 25 sudoku problem, took 15 min to solve in serial version 

`test25_28min.sdk`: a 25 * 25 sudoku problem, took 28 min to solve in serial version

`test36.sdk`: a 36 * 36 sudoku problem

`test100.sdk`: a 100 * 100 sudoku problem

`test144.sdk`: a 144 * 144 sudoku problem
