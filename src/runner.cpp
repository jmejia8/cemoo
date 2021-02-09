#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>

#include "NSGA-III.hpp"
#include "plot.hpp"

using namespace std;

void save_front(Individual* P, int pop_size, int nrun)
{

    printf("Saving\n");
	ofstream txt_file;
    int m = P[0].get_nfs();
    char fname[200];
    
    sprintf(fname, "pf-approx/dtlz2-%d-run%d.txt", m , nrun);
    txt_file.open(fname);
    std::cout << fname << std::endl;

    for (int i = 0; i < pop_size; ++i) {
        for (int j = 0; j < m; ++j) {
            txt_file << P[i].f[j] << " ";
        }
        txt_file << endl;
    }
    txt_file.close();
    printf("save done\n");
}




int run(int population_size, int dim, int m, int max_gen, int nrun)
{

    double** bounds = fmatrix(dim, 2);


    for (int i = 0; i < dim; ++i) {
        bounds[i][0] = 0.0;
        bounds[i][1] = 1.0;
    }


    Problem* p = new Problem(dim, m, bounds);
    NSGAIII* ga = new NSGAIII(p, population_size);
    ga->max_generations = max_gen;

    ga->p_c = 1.0;
    ga->p_m = 1.0 / (double) dim;
    ga->eta_c = 30;
    ga->eta_m = 20;


    printf("Running max gen %d\n", max_gen);
    ga->run();
    save_front(ga->population, ga->n_fronts[0], nrun+1);
    printf("run complete\n");


    Plot plt;
    // plt.scatter(ga->population, min( population_size, ga->n_fronts[0]));
    plt.scatter(ga->population, population_size);
    // plt.show();


    
    return 0;
}


int main(int argc, char *argv[]) {
    printf("Starting main...\n");
    // srand(time(NULL));

    /***
    int max_generations[2] = {600, 1000};
    int pops_size[2] = {212, 276};
    int ms[2] = {5, 10};
    int nruns = 2;
    ***/

     int population_size,  dim,  m,  max_gen,  nrun,  seed;


    std::cin >> population_size;
    std::cin >> m;
    std::cin >> max_gen;
    std::cin >> seed;

    /**
    population_size = 92;
    m = 3;
    max_gen = 250;
    seed = time(NULL);
    ***/

    nrun = seed;
    
    dim = m + 10 - 1;

    printf("population_size = %d\n", population_size);
    printf("m = %d\n", m);
    printf("max_gen = %d\n", max_gen);
    printf("nrun = %d\n", nrun);
    printf("seed = %d\n", seed);

    srand(seed);


    run(population_size,  dim,  m,  max_gen,  nrun);




}

