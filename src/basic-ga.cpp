#include <math.h>
#include "utils.h"
#include "population.hpp"
#include "random.h"
#include "basic-ga.hpp"
#include "external-problem.h"


GA::GA(Problem* problem_)
{
	problem = problem_;
}


GA::GA(Problem* problem_, int population_size_){
	problem = problem_;
	set_population_size(population_size_);

	ideal = fvector(problem->n_objectives);
	nadir = fvector(problem->n_objectives);
	utopian = fvector(problem->n_objectives);

	float Inf = 1.0 / 0.0;
	for (int i = 0; i < problem->n_objectives; ++i) {
		ideal[i]   = Inf;
		nadir[i]   = -Inf;
		utopian[i] = Inf;
	}
}


GA::~GA (){
	delete[] population;
	delete problem;


	free(ideal);
	free(nadir);
	free(utopian);
}


void GA::set_population_size(int population_size_)
{
	if (population_size != 0) {
		error("Genetic algorithm already initialized");
	}

	population_size = population_size_;
	// initialize pointers to individuals (parent and offsprings in same array)
	population = gen_population(2*population_size, true);
	offsprings = &population[population_size];

}

void GA::initialize_with_randoms()
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


void GA::eval_population()
{
	if (problem == NULL || population == NULL)
		error("Population seems empty.");

	float* f = fvector(problem->n_objectives);

	for (int i = 0; i < population_size; ++i) {
		objective_function(population[i].x, f, population_size, problem->n_objectives);
		population[i].set_f(f, problem->n_objectives);
		offsprings[i].set_f(f, problem->n_objectives);

		update_ideal(ideal, f, problem->n_objectives);
		update_nadir(nadir, f, problem->n_objectives);
	}


	free(f);
}

void GA::eval_offsprings()
{
	if (problem == NULL || population == NULL)
		error("Population seems empty.");

	float* f = fvector(problem->n_objectives);

	for (int i = 0; i < population_size; ++i) {
		objective_function(offsprings[i].x, f, population_size, problem->n_objectives);
		offsprings[i].set_f(f, problem->n_objectives);

		update_ideal(ideal, f, problem->n_objectives);
		update_nadir(nadir, f, problem->n_objectives);
	}


	free(f);
}





Individual* gen_population(int pop_size, bool init)
{
	Individual* tmp = (Individual*) malloc(sizeof(Individual) * pop_size );
	if (!init)
		return tmp;
	
	for (int i = 0; i < pop_size; ++i) {
		tmp[i] = Individual();
	}

	return tmp;
}
void permutate_population(Individual* pop, int* mask, int pop_size)
{

	Individual* pop_new = gen_population(pop_size, false);

	for (int i = 0; i < pop_size; ++i)
		pop_new[i] = pop[i];

	for (int i = 0; i < pop_size; ++i)
		pop[i] = pop_new[mask[i]];


}
