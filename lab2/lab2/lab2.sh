#!/bin/bash
#
#Процессор

lscpu | grep -i 'Model name' | awk '{print $3,$4,$5,$6}' > test.csv
g++ lab2.cpp -Werror -Wextra -Wall
read n
./a.out $n >> test.csv