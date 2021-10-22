#!/bin/bash
#

g++ -pthread lab5POSIX.cpp -Wextra -Wall -o posix.out
g++ -fopenmp lab5OPENMP.cpp -Wextra -Wall -o openmp.out
echo "POSIX result" > test.csv
./posix.out 100 8 >> test.csv
./posix.out 200 8 >> test.csv
./posix.out 300 8 >> test.csv
./posix.out 400 8 >> test.csv
./posix.out 500 8 >> test.csv
./posix.out 1000 8 >> test.csv
./posix.out 1500 8 >> test.csv
./posix.out 2000 8 >> test.csv
./posix.out 2500 8 >> test.csv
echo "OpenMP result" >> test.csv
./openmp.out 100 8 >> test.csv
./openmp.out 200 8 >> test.csv
./openmp.out 300 8 >> test.csv
./openmp.out 400 8 >> test.csv
./openmp.out 500 8 >> test.csv
./openmp.out 1000 8 >> test.csv
./openmp.out 1500 8 >> test.csv
./openmp.out 2000 8 >> test.csv
./openmp.out 2500 8 >> test.csv