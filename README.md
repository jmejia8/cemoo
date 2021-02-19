# NSGA-III

An implementation of this algorithm.


To run the algorithm for all experiments use `./run-exp.sh` (for 
5 objective of NSGA-III) `./run-zcat-exp.sh` (for 
10 objective of NSGA-III)

For a single run of the algorithm, use the `make && ./bin/runner  < input-example.txt` command. File `input-info.txt` contains more details.



The binary is saved in `bin/` after compilation with `make`. The 
implementation of NSGA-III is in `src/NSGA-III.cpp`. The results
are saved in folder `pf-approx/`.


