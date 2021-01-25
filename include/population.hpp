class Individual
{

private:
	int dimension;
	int n_objectives;

public:
	float* x = NULL;
	float* f = NULL;

	Individual (){};

	Individual (int dimension_, int n_objectives_){
		dimension = dimension_;
		n_objectives = n_objectives_;

		x = fvector(dimension);
		f = fvector(n_objectives);
	};
	virtual ~Individual (){
		free(x);
		free(f);
	}


	void set_x(float* x_new, int len){
		dimension = len;
		x = fvector(dimension);
		set_x(x_new);
	}

	void set_x(float* x_new){
		for (int i = 0; i < dimension; ++i) {
			x[i] = x_new[i];
		}
	}


	void set_f(float* f_new){
		for (int i = 0; i < dimension; ++i) {
			f[i] = f_new[i];
		}
	}


	void set_f(float* f_new, int len){
		n_objectives = len;
		f = fvector(n_objectives);
		set_f(f_new);
	}

};


Individual* gen_population(int pop_size){
	return (Individual*) malloc(sizeof(Individual) * pop_size );
}

void permutate_population(Individual* pop, int* mask, int pop_size)
{

	Individual* pop_new = gen_population(pop_size);

	for (int i = 0; i < pop_size; ++i)
		pop_new[i] = pop[i];

	for (int i = 0; i < pop_size; ++i)
		pop[i] = pop_new[mask[i]];


}

