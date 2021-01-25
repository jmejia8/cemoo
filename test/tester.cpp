#include <iostream>
#include <sort.h>
#include <utils.h>

#include "population.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    printf("Hola mundo\n");

    int pop_size = 10;
    Individual* pop = gen_population(pop_size) ;
    int* mask = ivector(pop_size);


    for (int i = 0; i < pop_size; ++i) {
        pop[i] = Individual();
        pop[i].set_x(fvector(7), 7);
        pop[i].x[0] = (float)i;
        printf("%f ", pop[i].x[0]);
        mask[i] = pop_size - i - 1;
    }


    permutate_population(pop, mask, pop_size);

    printf("\n---------\n");

    for (int i = 0; i < pop_size; ++i) {
        printf("%f ", pop[i].x[0]);
    }
    printf("\n");


    
    return 0;
}
