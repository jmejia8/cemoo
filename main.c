#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// load functions to find non dominated sets
#include "get-no-dominated.c"

// read txt with space separated values
#include "read-txt.c"

int main(int argc, char *argv[])
{
    int pop_size, n;
    int n_non_dominated;

    clock_t start, end;
    double cpu_time_used;
     
    float* fvals;

    //method_one(data, non_dominated, pop_size, &n_non_dominated, n);
    if( argc == 2 ) {
        fvals = read_txt(argv[1], &pop_size, &n);
    }else{
        error("File is required.");
    }


    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    int non_dominated[pop_size];
    int method;

    for (method = 1; method < 4; ++method) {
        printf("Method = %d\n", method);

        start = clock();
        get_non_dominated(fvals, non_dominated, pop_size, &n_non_dominated, n, method);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("non dominated = %d\n", n_non_dominated);
        printf("time: %lf\n\n", cpu_time_used);
    }



    return 0;
}
