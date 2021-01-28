#ifndef NSGA_III_H
#define NSGA_III_H


#include "basic-ga.hpp"

class NSGAIII: public GA {
    private:
        int* parent;

	public:
		float di = 10.0;
		float dim = 50.0;
        int* fronts = NULL, *n_fronts = NULL;

		NSGAIII(Problem* problem_) ;
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


};

#endif
