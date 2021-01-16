#include <stdio.h>
#include <stdlib.h>
#include "get-no-dominated.c"
#include "read-txt.c"

int main(int argc, char *argv[])
{
    // float* data = {
    //         4.0, 2.0, 3.0,
    //         3.0, 2.0, 5.0,
    //         1.0, 5.0, 4.0,
    //         2.0, 3.0, 0.0,
    //         1.0, 3.0, 8.0,
    //         6.0, 0.0, 1.0,
    //         8.0, 2.0, 2.0,
    //         3.0, 1.0, 5.0, 
    //         4.0, 4.0, 5.0,
    //         9.0, 1.0, 1.0
    // };


    int pop_size, n;
    int n_non_dominated;
    int non_dominated[pop_size];

    float* fvals;
    //method_one(data, non_dominated, pop_size, &n_non_dominated, n);
    read_txt("example1.txt", fvals, &pop_size, &n);

    printf("afd\n");





    return 0;
}
