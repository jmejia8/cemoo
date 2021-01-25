#include <iostream>
#include <sort.h>
#include <utils.h>

#include "population.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    printf("Hola mundo\n");

    Individual pop[10];

    pop[0].set_x(fvector(7), 7);

    for (int i = 0; i < 7; ++i) {
        printf("%f\n", pop[0].x[i]);
    }

    permutate_population(pop);

    
    return 0;
}
