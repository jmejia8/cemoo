#ifndef GA_H
#define GA_H

#include "utils.h"
#include "population.hpp"

Individual* gen_population(int pop_size, bool init);
void permutate_population(Individual* pop, int* mask, int pop_size);

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
	~GA ();
	GA(Problem* problem_);
	void set_population_size(int population_size_);
	void initialize_with_randoms();
    void eval_population();
    void eval_offsprings();
	void update_population();



	
};


#endif
