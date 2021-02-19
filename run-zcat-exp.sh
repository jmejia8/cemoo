#!/bin/bash
mkdir output
make clean
make
for i in {1..30}
do
   echo "$i"
   (cat input-zcat.txt && echo "$i" ) > tmp.txt 
   ./bin/runner < tmp.txt
done
