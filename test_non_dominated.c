#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// load functions to find non dominated sets
#include "get-no-dominated.c"

// read txt with space separated values
#include "read-txt.c"

void test(char* instance, int n_non_dominated_true)
{
    int pop_size, n;

    clock_t start, end;
    double cpu_time_used;
     
    float* fvals;


    fvals = read_txt(instance, &pop_size, &n);


    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    int non_dominated[pop_size];
    int n_non_dominated;
    int method;

    printf("+--------------------------------+\n");
    for (method = 1; method < 4; ++method) {
        printf("Method: %d\t", method);
        printf("instance: %s\t", instance);

        start = clock();
        get_non_dominated(fvals, non_dominated, pop_size, &n_non_dominated, n, method);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("# non dominated: %d\t", n_non_dominated);
        printf("time: %lf\n", cpu_time_used);

        // are equal?
        if ( n_non_dominated != n_non_dominated_true ) {
            error("Test not passed.");
        }
    }

}


int main(int argc, char *argv[])
{

    if( argc != 2 ) {
        error("File is required.");
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        error("cannot open file.");
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char fname[264];
    int N;

    while ((read = getline(&line, &len, file)) != -1) {
        if(line[0] == '\n')
            continue;
        sscanf(line, "%s %d", fname, &N);
        test(fname, N);
    }


    printf("\nAll test passed. :D\n");
    
    return 0;
}
