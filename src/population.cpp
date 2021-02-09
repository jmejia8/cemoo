#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "population.hpp"

Individual::Individual (){}

Individual::Individual (int dimension_, int n_objectives_)
{
	dimension = dimension_;
	n_objectives = n_objectives_;

	x = fvector(dimension);
	f = fvector(n_objectives);
};


Individual::~Individual ()
{
	free(x);
	free(f);
}


void Individual::set_x(double* x_new, int len)
{
	dimension = len;
	x = fvector(dimension);
	set_x(x_new);
}

void Individual::set_x(double* x_new)
{
	for (int i = 0; i < dimension; ++i) {
		x[i] = x_new[i];
	}
}


void Individual::set_f(double* f_new)
{
	for (int i = 0; i < n_objectives; ++i) {
		f[i] = f_new[i];
	}
}


void Individual::set_f(double* f_new, int len)
{
	n_objectives = len;
	f = fvector(n_objectives);
	set_f(f_new);
}

int Individual::get_dim()
{
	return dimension;
}

int Individual::get_nfs()
{
	return n_objectives;
}

