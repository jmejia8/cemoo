#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "get-no-dominated.c"
#include "read-txt.c"

void print_fvals(float* fvals, int pop_size, int n){
    int i, j;
    for (i = 0; i < pop_size; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%f ", fvals[i*n + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int pop_size, n;
    int n_non_dominated;

    clock_t start, end;
    double cpu_time_used;
     

    //method_one(data, non_dominated, pop_size, &n_non_dominated, n);
    float* fvals = read_txt("txt/example_3000_5.txt", &pop_size, &n);
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


    return 0;
}
