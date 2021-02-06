#ifndef NSGA_III_H
#define NSGA_III_H


#include "basic-ga.hpp"

class NSGAIII: public GA {
    private:
        int* parent;

	public:
		float eta_c = 30.0;
		float eta_m = 20.0;
        int* fronts = NULL, *n_fronts = NULL;
        float** ref_dirs = NULL;
        int n_ref_dirs = 0;
        int n_partitions = 12;

		NSGAIII(Problem* problem_) ;
        NSGAIII(Problem* problem_, int population_size);
        ~NSGAIII();

        void gen_parents();
        void crossover();
        void mutate();
        void update_fronts(int);
        void survival();
        void restart_fronts();
        void run();

		void sbx();
		void realmutate();

		void associate_to_niches();
		void normalize();
        void niching(int K, int* rho, int* pi, float* distances_s_to_w, int* last_front, int last_front_size);
        void update_ideal_nadir(int* non_dominated, int len);

};

#endif
