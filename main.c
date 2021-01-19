#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "get-no-dominated.c"
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

    int non_dominated[pop_size];


    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    start = clock();
    method_one(fvals, non_dominated, pop_size, &n_non_dominated, n);
    end = clock();


    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("non dominated = %d\n", n_non_dominated);
    printf("time: %lf\n", cpu_time_used);

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    start = clock();
    method_two(fvals, non_dominated, pop_size, &n_non_dominated, n);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("non dominated = %d\n", n_non_dominated);
    printf("time: %lf\n", cpu_time_used);


    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    start = clock();
    method_three(fvals, non_dominated, pop_size, &n_non_dominated, n);
    end = clock();


    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("non dominated = %d\n", n_non_dominated);
    printf("time: %lf\n", cpu_time_used);

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    return 0;
}
