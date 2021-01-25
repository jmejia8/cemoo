#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// load functions to find non dominated sets
#include "get-no-dominated.h"
#include "utils.h"

// read txt with space separated values
#include "read-txt.h"

int main(int argc, char *argv[])
{
    int pop_size, n;
    int n_non_dominated;

    clock_t start, end;
    double cpu_time_used;
    int method;
     
    float* fvals;

    //method_one(data, non_dominated, pop_size, &n_non_dominated, n);
    if( argc == 3 ) {
        fvals = read_txt(argv[1], &pop_size, &n);
        sscanf(argv[2], "%d", &method);
    }else{
        error("File and method number is required.\nUsage: ./main.bin txt/example_3000_5.txt 1");
    }


    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    int non_dominated[pop_size];

    printf("Method = %d\n", method);

    start = clock();
    get_non_dominated(fvals, non_dominated, pop_size, &n_non_dominated, n, method);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("non dominated = %d\n", n_non_dominated);
    printf("time: %lf\n\n", cpu_time_used);

    int i;

    for (i = 0; i < n_non_dominated; ++i) {
        printf("%d ", non_dominated[i] + 1);
    }

    printf("\n");


    return 0;
}
