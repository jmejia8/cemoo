class Individual
{

private:
	int dimension;
	int n_objectives;

public:
	float* x;
	float* f;

	Individual (int dimension_, int n_objectives_){
		dimension = dimension_;
		n_objectives = n_objectives_;

		x = (float*) malloc( dimension * sizeof(float) );
		f = (float*) malloc( n_objectives * sizeof(float) );
	};
	virtual ~Individual (){
		free(x);
		free(f);
	}

};


Individual::set_x(float* x_new){
	for (int i = 0; i < dimension; ++i) {
		x[i] = x_new[i];
	}
}


Individual::set_f(float* f_new){
	for (int i = 0; i < dimension; ++i) {
		f[i] = f_new[i];
	}
}


class Population
{
public:
	int size;
	Individual* population;

	Population (int size_){
		size = size_;
		population = (Individual * ) malloc(size * sizeof(Individual));

	}

	virtual ~Population (){
		delete[] population;
	}

	
};


Population::initilize(int dimension, int n_objectives, float bounds[size][2]){
	float* x = fvector(dimension);
	float* f = fvector(n_objectives);

	for (int i = 0; i < size; ++i) {
		population[i] = new Individual(dimension, n_objectives);
		population[i].set_x(x);
		population[i].set_f(f);
	}
}

Population::permutate(int* mask){
	Individual temp[size];
	for (int i = 0; i < size; ++i) {
		
	}
}
