#ifndef POPULATION_H
#define POPULATION_H

#include <stdlib.h>

class Individual
{

	private:
		int dimension;
		int n_objectives;

	public:
		float* x = NULL;
		float* f = NULL;
		int rank;
		int nich;
		float distance_to_nich;

		Individual ();

		Individual (int dimension_, int n_objectives_) ;

		virtual ~Individual ();

		void set_x(float* x_new, int len);
		void set_x(float* x_new);
		void set_f(float* f_new);
		void set_f(float* f_new, int len);
		int get_dim();
		int get_nfs();


};


#endif
