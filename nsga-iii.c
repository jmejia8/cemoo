#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "utils.c"
#include "random.c"
#include "problem.c"

typedef struct {
    // decision variables
    float* positions;
    // objective function values
    float* fvalues;
    // population size
    int N;

    // decision variable dimension
    int n;
    
    // no. of objective functions
    int m;
} Population;

void initialize(Population* P)
{

    printf("initialize\n");
    P->positions = fvector(P->N * P->n);
    P->fvalues = fvector(P->N * P->m);


    int i;
    float* x;
    float* F;
    for (i = 0; i < P->N; ++i) {
        x = &P->positions[i * P->n];
        F = &P->fvalues[i * P->m];

        fill_random(0, 1.0, x, P->n) ;
        objective_function(x, F, P->n, P->m);
    }

}


int main(int argc, char *argv[])
{
    
    Population P;

    P.N = 11;
    P.m = 3;
    P.n = 5;

    initialize(&P);

    printf("Population:\n");
    print_matrix(P.positions, P.N, P.n);

    printf("\nF values:\n");
    print_matrix(P.fvalues, P.N, P.m);

    printf("P.N = %d\n", P.N);
    return 0;
}

