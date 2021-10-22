#!/bin/bash
#

g++ lab4.cpp -Werror -Wextra -Wall
./a.out 100 > test.csv
./a.out 200 >> test.csv
./a.out 300 >> test.csv
./a.out 400 >> test.csv
./a.out 500 >> test.csv