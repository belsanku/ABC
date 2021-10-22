#!/bin/bash
#

g++ lab3.cpp -Werror -Wextra -Wall
p="$–m RAM –b 64 –l 10"
./a.out $p > test1.csv
p="$–m RAM –b 393216 –l 10"
./a.out $p >> test1.csv
p="$–m RAM –b 2097152 –l 10"
./a.out $p >> test1.csv
p="$–m RAM –b 4194304 –l 10"
./a.out $p >> test1.csv
p="$–m RAM –b 42043040 –l 10"
./a.out $p >> test1.csv
i=0
memSize=4194304
while [ $i -lt 20 ] 
do
p="$-m SSD -b $memSize -l 10"
memSize=$(($memSize+4194304))
./a.out $p >> test1.csv
i=$(($i+1))
done