#ifndef GA_H
#define GA_H

#include "population.hpp"
#include "random.h"

class Problem
{
public:
	int dimension = 0, n_objectives = 0;
	float** bounds;

	Problem ();
	Problem (int dimension_, int n_objectives_, float* bounds_[]){
		dimension = dimension_;
		n_objectives = n_objectives_;
		bounds = fmatrix(dimension, 2);
		for (int i = 0; i < dimension; ++i) {
			bounds[i][0] = bounds_[i][0];
			bounds[i][1] = bounds_[i][1];
		}
	}

	virtual ~Problem (){
		delete bounds;
	}

};

class GA
{
public:

	int population_size = 0;
	int max_generations = 100; // maximum number of generations
	float p_m = 0.01; // mutation probability
	float p_c = 0.9; // crossover probability
	Individual* population = NULL;
	Individual* offsprings = NULL;
	Problem* problem = NULL;


	GA ();
	GA(Problem* problem_)
	{
		problem = problem_;
	}
	virtual ~GA (){
		delete[] population;
		delete problem;
	}


	void set_population_size(int population_size_) {
		if (population_size != 0) {
			error("Genetic algorithm already initialized");
		}

		population_size = population_size_;
		// initialize pointers to individuals (parent and offsprings in same array)
		population = gen_population(2*population_size, true);
		offsprings = &population[population_size];

	}

	void initialize_with_randoms()
	{
		if (problem == NULL)
			error("Instantiate with a problem.");

		// initialize with random values
		float* pop = fvector(population_size * problem->dimension); 
		float* x;
		fill_population(pop, population_size, problem->dimension, problem->bounds);
		for (int i = 0; i < population_size; ++i) {
			x = &pop[i*problem->dimension];
			population[i].set_x(x, problem->dimension);
			offsprings[i].set_x(x, problem->dimension);
		}

		free(pop);
	}


    void eval_population()
	{
		if (problem == NULL || population == NULL)
			error("Population seems empty.");
		
		float* f = fvector(problem->n_objectives);

		for (int i = 0; i < population_size; ++i) {
			objective_function(population[i].x, f, population_size, problem->n_objectives);
			population[i].set_f(f, problem->n_objectives);
			offsprings[i].set_f(f, problem->n_objectives);
		}


		free(f);
	}
    void eval_offsprings()
	{
		if (problem == NULL || population == NULL)
			error("Population seems empty.");
		
		float* f = fvector(problem->n_objectives);

		for (int i = 0; i < population_size; ++i) {
			objective_function(offsprings[i].x, f, population_size, problem->n_objectives);
			offsprings[i].set_f(f, problem->n_objectives);
		}


		free(f);
	}


	void update_population();



	
};

#endif

