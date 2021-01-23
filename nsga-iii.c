#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include "get-no-dominated.c"
#include "random.c"
#include "problem.c"
#include "read-txt.c"
#include "crossover.c"
#include "mutation.c"


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


void fill_population(float* positions, int N, int n, float bounds[n][2]){
    int i, j;
    float l;
    for (j = 0; j < n; ++j) {
        l = bounds[j][1] - bounds[j][0];
        for (i = 0; i < N; ++i) {
            positions[i*n + j] = bounds[j][0] + l*rand01();
        }
    }

}

void initialize(Population* P, float bounds[P->n][2])
{

    printf("initialize\n");
    P->positions = fvector(P->N * P->n);
    P->fvalues = fvector(P->N * P->m);


    int i;
    float* x;
    float* F;

    fill_population(P->positions, P->N, P->n, bounds);

    for (i = 0; i < P->N; ++i) {
        F = &P->fvalues[i * P->m];
        x = &P->positions[i * P->n];
        objective_function(x, F, P->n, P->m);
    }

}


int main(int argc, char *argv[])
{
    // srand(time(0));
    Population P;

    P.N =  5000;
    P.m = 5;
    P.n = P.m + 10 - 1;
    float di = 20.5;
    float dim = 20.0;

    float bounds[P.n][2];
    int i;
    for (i = 0; i < P.n; ++i) {
        bounds[i][0] = 0.0;
        bounds[i][1] = 1.0;
    }


    initialize(&P, bounds);

    float* new_pop = fvector(P.N*P.m);


    printf("Population:\n");
    //print_matrix(P.positions, P.N, P.n);
    printf("epale\n");

    realcross(new_pop, P.positions, P.N, P.n, 0.9, bounds, di);
    return 0;
    printf("--------------------------------- after cross:\n");
    //print_matrix(new_pop, P.N, P.n);
    realmutate(new_pop, P.N, P.n, 0.01, dim, bounds);
    printf("--------------------------------- after mut:\n");
    //print_matrix(new_pop, P.N, P.n);
    printf("---------------------------------\n");
    return 0;

    printf("\nF values:\n");
    // print_matrix(P.fvalues, P.N, P.m);
    printf("\n");


    int* non_dominated = ivector(P.N);
    int k;


    get_non_dominated(P.fvalues, non_dominated, P.N, &k, P.m, 3);

    for (i = 0; i < k; ++i) {
        printf("%03d: ", non_dominated[i]);
        print_matrix(&P.fvalues[ non_dominated[i]* P.m ], 1, P.m);
    }
    printf("\n");

    printf("no dominated = %d\n", k);
    return 0;
}

