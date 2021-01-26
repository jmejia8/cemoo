#ifndef NSGA_II_H

#include "basic-ga.hpp"
#include "get-no-dominated.h"



class NSGAIII: public GA {
    private:
        int* fronts = NULL, *n_fronts = NULL;
        int* parent;

	public:
		float di = 20.0;

		NSGAIII(Problem* problem_) 
			: GA{problem_}
		{
		}
        ~NSGAIII(){
            free(fronts);
            free(n_fronts);
        }

        void gen_parents();
        void crossover();
        void mutate();
        void update_fronts(int);
        void survival();
        void restart_fronts();
        void run();

		void sbx();


};



void NSGAIII::run()
{

    float start = ttime();
    initialize_with_randoms();
    eval_population();
    gen_parents();
    crossover();
    mutate();
    update_fronts(2*population_size);
    survival();
    std::cout << "time in second: " << ttime() - start << std::endl;


}


void NSGAIII::crossover(){
	sbx();

}


/*
 * This is the file used for crossover for Real Coded GA
 * adapted from original code
 * 
 * */
void NSGAIII::sbx()
{
	int i,j,y,n;
	float rnd,par1,par2,chld1,chld2,betaq,beta,alpha;
	float y1,y2,yu,yl,expp;
	int popsize = population_size;
	int nvar = problem->n_objectives;
	float pcross = p_c;
	float** lim_r = problem->bounds;

	Individual* new_pop_ptr = offsprings;


	y=0; n=0;
	for(i = 0; i < popsize/2; i++)
	{
		rnd = rand01();

		/*Check Whether the cross-over to be performed*/
		if(rnd <= pcross)
		{

			/*Loop over no of variables*/
			for(j = 0;j < nvar;j++)
			{ 
				/*Selected Two Parents*/ 
				par1 = population[parent[y]].x[j];
				par2 = population[parent[y+1]].x[j]; 

				yl = lim_r[j][0];
				yu = lim_r[j][1];

				rnd = rand01();

				/* Check whether variable is selected or not*/
				if(rnd <= 0.5)
				{
					/*Variable selected*/
					//ncross++;

					if(fabs(par1 - par2) > 0.000001) // changed by Deb (31/10/01)
					{
						if(par2 > par1)
						{
							y2 = par2;
							y1 = par1;
						}
						else
						{
							y2 = par1;
							y1 = par2;
						}

						/*Find beta value*/
						if((y1 - yl) > (yu - y2))
						{
							beta = 1 + (2*(yu - y2)/(y2 - y1));
							//printf("beta = %f\n",beta);
						}
						else
						{
							beta = 1 + (2*(y1-yl)/(y2-y1));
							//printf("beta = %f\n",beta);
						}

						/*Find alpha*/
						expp = di + 1.0;

						beta = 1.0/beta;

						alpha = 2.0 - pow(beta,expp);

						if (alpha < 0.0) 
						{
							printf("ERRRROR %f %d %d %f %f\n",alpha,y,n,par1,par2);
							exit(-1);
						}

						rnd = rand01(); 

						if (rnd <= 1.0/alpha)
						{
							alpha = alpha*rnd;
							expp = 1.0/(di+1.0);
							betaq = pow(alpha,expp);
						}
						else
						{
							alpha = alpha*rnd;
							alpha = 1.0/(2.0-alpha);
							expp = 1.0/(di+1.0);
							if (alpha < 0.0) 
							{
								printf("ERRRORRR \n");
								exit(-1);
							}
							betaq = pow(alpha,expp);
						}

						/*Generating two children*/
						chld1 = 0.5*((y1+y2) - betaq*(y2-y1));
						chld2 = 0.5*((y1+y2) + betaq*(y2-y1));

					}
					else
					{

						betaq = 1.0;
						y1 = par1; y2 = par2;

						/*Generation two children*/
						chld1 = 0.5*((y1+y2) - betaq*(y2-y1));
						chld2 =  0.5*((y1+y2) + betaq*(y2-y1));

					}
					// added by deb (31/10/01)
					if (chld1 < yl) chld1 = yl;
					if (chld1 > yu) chld1 = yu;
					if (chld2 < yl) chld2 = yl;
					if (chld2 > yu) chld2 = yu;
				}
				else
				{

					/*Copying the children to parents*/
					chld1 = par1;
					chld2 = par2;
				}
				new_pop_ptr[n].x[j] = chld1;
				new_pop_ptr[(n+1)].x[j] = chld2;
			}
		}
		else
		{
			for(j = 0;j < nvar;j++)
			{
				par1 = population[parent[y]].x[j];
				par2 = population[parent[y+1]].x[j]; 
				chld1 = par1;
				chld2 = par2;
				new_pop_ptr[n].x[j] = chld1;
				new_pop_ptr[(n+1)].x[j] = chld2;
			}
		}
		n = n+2; y=y+2;
	}
	return;
}



void NSGAIII::mutate()
{

}


void NSGAIII::survival()
{
    if (n_fronts == NULL)
        error("first run update_fronts() method");

	// parent and offspring
    permutate_population(population, fronts, 2*population_size);

    restart_fronts();
    
}


void NSGAIII::gen_parents()
{
    if (parent == NULL){
        parent = ivector(population_size);
        for (int i = 0; i < problem->dimension; ++i) {
            parent[i] = i;
        }
    }

    // generate a random permutation
    randperm(parent, population_size);
    
}


void NSGAIII::restart_fronts()
{
    
	// parent and offspring
    if (fronts == NULL)
        fronts = ivector(2*population_size);
    if (n_fronts == NULL)
        n_fronts = ivector(2*population_size);

    for (int i = 0; i < 2*population_size; ++i) {
        fronts[i] = i;
    }
}

/*
 *
 * fronts = {i | i in fronts}
 * n_fronts[i] size of fronts[i]
 * https://github.com/msu-coinlab/pymoo/blob/master/pymoo/util/nds/fast_non_dominated_sort.py
 * 
 * */
void NSGAIII::update_fronts(int pop_size)
{
    // int pop_size = population_size;
    int n = problem->n_objectives;


    if (fronts == NULL)
        fronts = ivector(pop_size);
    if (n_fronts == NULL)
        n_fronts = ivector(pop_size);

    int i, j, ii, jj;
    char rel;
    for (i = 0; i < pop_size; ++i) {
        fronts[i] = 0;
        n_fronts[i] = 0;
    }

    // step 1
    int** is_dominating = imatrix(pop_size, pop_size);
    int n_is_dominating[pop_size];
    int n_dominated[pop_size];
    int n_current_front;
    int n_ranked = 0;
    
    for (i = 0; i < pop_size; ++i) {
        n_dominated[i] = 0;
        n_fronts[i] = 0;
        n_is_dominating[i] = 0;

    }

    for (i = 0; i < pop_size; ++i) {
        for (j = i+1; j < pop_size; ++j) {
            rel = compare(population[i].f, population[j].f, n);
            // j domiates i?
            if(rel == 'D'){
                is_dominating[j][n_is_dominating[j]] = i;
                n_dominated[i] += 1;
                n_is_dominating[j] += 1;
            // i domiates j?
            }else if (rel == 'd'){
                is_dominating[i][n_is_dominating[i]] = j;
                n_dominated[j] += 1;
                n_is_dominating[i] += 1;
            }
        }

        // no-body dominates i?
        if (n_dominated[i] == 0) {
            //ranked[i] = 1.0;
            fronts[n_ranked++] = i;
        }

    }

    // size of current front
    n_fronts[0] = n_ranked;


    n_current_front = 0;
    int* current_front = fronts;
    int n_ranked_old = n_ranked;

    // while not all solutions are assigned to a pareto front
    while(n_ranked < pop_size) {
        // for each individual in the current front
        for (ii = 0; ii < n_fronts[ n_current_front ]; ++ii) {
            i = current_front[ii];


            // all solutions that are dominated by this individual
            for (jj = 0; jj < n_is_dominating[i]; ++jj) {
                
                j = is_dominating[i][jj];

                n_dominated[j] -= 1;
                
                if (n_dominated[j] == 0) {
                    // current front
                    fronts[ n_ranked ] = j;
                    // ranked[j] = 1.0;

                    // next front size
                    ++n_fronts[ n_current_front + 1 ];
                    ++n_ranked;
                }

            }
        }

        if (n_fronts[ n_current_front + 1 ] == 0) {
            error("empty front found.");
        }

        ++n_current_front;
        // move to next front
        current_front = &fronts[ n_ranked_old ];
        n_ranked_old = n_ranked;
    }


    for (i = 0; i < pop_size; ++i) {
        free(is_dominating[i]);
    }
    

}


#endif
