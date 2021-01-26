#include <iostream>
#include <sort.h>
#include <utils.h>
#include <time.h>

#include "external_problem.h"
#include "population.hpp"
#include "NSGA-III.hpp"
#include "Plot.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    printf("Hola cara de bola\n");
    srand(time(NULL));

    int population_size = 100;
    int m = 2;
    int dim = m + 10 - 1;
    float** bounds = fmatrix(dim, 2);


    for (int i = 0; i < dim; ++i) {
        bounds[i][0] = 0.0;
        bounds[i][1] = 1.0;
    }


    Problem* p = new Problem(dim, m, bounds);

    NSGAIII* ga = new NSGAIII(p);
    ga->max_generations = 500;

    ga->set_population_size(population_size);
    ga->run();


    Plot plt;

    plt.scatter(ga->population, ga->n_fronts[0]);
    plt.show();

    printf("adiosin\n");


    
    return 0;
}
