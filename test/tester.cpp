#include <iostream>
#include <sort.h>
#include <utils.h>

#include "external_problem.h"
#include "population.hpp"
#include "NSGA-III.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    printf("Hola cara de bola\n");



    int population_size = 100;
    int m = 5;
    int dim = m + 10 - 1;
    float** bounds = fmatrix(dim, 2);


    for (int i = 0; i < dim; ++i) {
        bounds[i][0] = -1.0;
        bounds[i][1] = 10.0;
    }


    Problem* p = new Problem(dim, m, bounds);

    NSGAIII* ga = new NSGAIII(p);

    ga->set_population_size(population_size);
    ga->run();


    printf("adiosin\n");


    
    return 0;
}
