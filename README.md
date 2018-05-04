# CS205_Sudoku
Spring 2018 Harvard CS 205 Final Project

Group 1: Shiyun Qiu, Xiangru Shu, Yiqi Xie, Yuyue Wang

# Introduction

# How-to-use

## Download source code

To run our sudoku solver, first download our [source code](https://github.com/shiyunqiu/CS205_Sudoku).

## Set up

As our program requires OpenMP and MPI, we recommend using AWS to run our code. To set up AWS environment, we followed the guides provided by CS205: [OpenMP](https://canvas.harvard.edu/courses/37285/files/5490479?module_item_id=363501) and [MPI](https://canvas.harvard.edu/courses/37285/files/5490480?module_item_id=363500).

After connecting to the AWS instance, copy the source code from local to the AWS instance using the following command:

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

Then you should be able to run the program by use the following commands:

```
make
```

```
run
```

## Serial
To run serial version



## OpenMP
## OpenMP + MPI

