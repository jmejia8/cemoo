#include <iostream>
#include <time.h>

#include "NSGA-III.hpp"
#include "plot.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    printf("Starting main...\n");
    srand(time(NULL));

    int population_size = 92;
    int m = 3;
    int dim = 10;
    float** bounds = fmatrix(dim, 2);


    for (int i = 0; i < dim; ++i) {
        bounds[i][0] = 0.0;
        bounds[i][1] = 1.0;
    }


    Problem* p = new Problem(dim, m, bounds);

    NSGAIII* ga = new NSGAIII(p, population_size);
    ga->max_generations = 250;

    ga->run();


    Plot plt;

    plt.scatter(ga->population, ga->n_fronts[0]);
    //plt.show();


    
    return 0;
}
