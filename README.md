# Parallelized Giant Sudoku Solver
### CS 205 Final Project, Spring 2018 Harvard 
### Group 1: Shiyun Qiu, Xiangru Shu, Yiqi Xie, Yuyue Wang

# Introduction

Sudoku is a combinatorial number placement puzzle. The objective of this game is to fill a 9×9 grid (board) with digits so that each column, each row, and each of the nine 3×3 subgrids (boxes) contains all of the digits from 1 to 9. Higher-rank sudokus usually have <a href="https://www.codecogs.com/eqnedit.php?latex=n^2*n^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n^2*n^2" title="n^2*n^2" /></a> board with <a href="https://www.codecogs.com/eqnedit.php?latex=n*n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n*n" title="n*n" /></a> boxes (n>3). However, higher-rank sudokus take hours to run in serial. Thus, we aim to parallelize a sudoku solver algorithm with several parallelization techniques (OpenMP and MPI), so that giant sudoku solver can be solved within a limited time.

# How-to-use

## Download Source Code

To run our sudoku solver, first download our [source code and test cases](https://github.com/shiyunqiu/CS205_Sudoku).

## Set Up

We adapt our code to AWS t2.2xlarge instances with Ubuntu 16.04.4 LTS. To set up an AWS cluster with OpenMP and MPI configured, we followed the guides provided by CS205: [OpenMP](https://canvas.harvard.edu/courses/37285/files/5490479?module_item_id=363501) and [MPI](https://canvas.harvard.edu/courses/37285/files/5490480?module_item_id=363500). After the setup, you should have:

 - enabled passwordless ssh between any pair of cluster nodes with username `mpiuser`
 - created the directory `/home/mpiuser/cloud` on the master node and made it shared by all the others
 - configured the MPI environment using ports 10000-10100
 - installed `mpich`

In addition, as we use makefile to compile our code, you need to install `build-essential`. To nail this down, run the following command line on the master node:

```
$ sudo apt-get install build-essential
```


## Run
 
Upload our source code and test cases to the master node. You may use the following command lines:

```
$ scp -i [ssh key] <parent directory>/src/* mpiuser@<master node public IP>:~/cloud/src
$ scp -i [ssh key] <parent directory>/test_cases/* mpiuser@<master node public IP>:~/cloud/test_cases
```

Connect to your master node on AWS, log in as `mpiuser` and change directory to `cloud/src`. You can build the program with command line:

```
$ make
```

This creates an executable named `run`. By default it solves a relatively simple test case with serial algorithm. You may configure the program to use parallel algorithms in `main.cpp`, where detailed instructions can be found.

To run the serial solver, simply type

```
$ ./run
```

In your terminal. The OpenMP version can be executed in the same way. However, if you want to tune the number of threads, you can specify it as an environment variable:

```
$ export OMP_NUM_THREADS=<the number of threads you want>
```

To execute the MPI versions, you have to use the `mpirun` keyword:

```
$ mpirun -np [number of processes] -hosts [list of hostnames] ./run
```

For example, to use 4 nodes with 1 process per node, the command line is like:
```
$ mpirun -np 4 -hosts master,node1,node2,node3,node4 ./run
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
