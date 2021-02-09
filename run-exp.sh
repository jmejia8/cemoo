#!/bin/bash
mkdir output
make clean
make
for i in {1..21}
do
   echo "$i"
   (cat input.txt && echo "$i" ) > tmp.txt 
   ./bin/runner < tmp.txt
done
