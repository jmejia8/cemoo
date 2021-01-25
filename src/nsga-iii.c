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

void eval_population(Population* P, int eval_offspring)
{

    int i, N=P->N, N0=0;
    float* x;
    float* F;


    if (eval_offspring){
        N0 = P->N;
        N  = 2*P->N;
    }


    for (i = N0; i < N; ++i) {
        F = &P->fvalues[i * P->m];
        x = &P->positions[i * P->n];
        objective_function(x, F, P->n, P->m);
    }




}

void initialize(Population* P, float bounds[P->n][2])
{

    // pistions for parents and children
    P->positions = fvector(2*P->N * P->n);
    P->fvalues = fvector(2*P->N * P->m);


    fill_population(P->positions, P->N, P->n, bounds);
    // eval parent
    eval_population(P, 0);


}

void genetic_algorithm()
{
    
    // srand(time(0));
    int i, j, ii, gen;

    Population P;
    float p_cross = 0.9;
    float di = 20.5;

    float p_mut = 0.01;
    float dim = 20.0;
    int generations = 100;


    P.N = 100;
    P.m = 5;
    P.n = P.m + 10 - 1;

    float bounds[P.n][2];
    for (i = 0; i < P.n; ++i) {
        bounds[i][0] = 0.0;
        bounds[i][1] = 1.0;
    }


    initialize(&P, bounds);


    ///////////////////
    ///////////////////
    ///////////////////
    float* children = &P.positions[P.N*P.n];
    float* new_pop = fvector(P.N*P.n);
    float* new_fvalues = fvector(P.N*P.m);
    int* fronts = ivector(2*P.N);
    int* fronts_sizes = ivector(2*P.N);
    ///////////////////
    ///////////////////
    ///////////////////



    printf("Initialization done!\n");

    for (gen = 0; gen < generations; ++gen) {
        printf("========================================\n");
        printf("========         GENERATION %d  =======\n", gen+1);
        printf("========================================\n");

        realcross(children, P.positions, P.N, P.n, p_cross, bounds, di);
        printf("Crossover done!\n");

        realmutate(children, P.N, P.n, p_mut, dim, bounds);
        printf("Mutation done!\n");

        // eval offsprings
        eval_population(&P, 1);
        printf("eval offsprings done!\n");

        fast_non_dominated(P.fvalues, fronts, fronts_sizes, 2*P.N, P.m);
        printf("Domination sort done!\n");
        printf("fronts_sizes[0] = %d\n", fronts_sizes[0]);

        for (i = 0; i < P.N; ++i) {
            ii = fronts[i];
            for (j = 0; j < P.n; ++j) {
                new_pop[i*P.n + j] = P.positions[ii * P.n + j];
            }
        }


        for (i = 0; i < P.N; ++i) {
            for (j = 0; j < P.n; ++j) {
                P.positions[i*P.n + j] = new_pop[i * P.n + j];
            }
        }



    }

    print_matrix(P.fvalues, P.N, P.m);

}

int main(int argc, char *argv[])
{

    genetic_algorithm();

    // free(fronts);
    // free(fronts_sizes);
    // free(P.positions);
    // free(P.fvalues);
    // free(new_pop);

    return 0;
}

