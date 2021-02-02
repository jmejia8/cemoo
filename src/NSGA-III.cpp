#include <fstream>
#include <iostream>
#include <math.h>

#include "utils.h"
#include "random.h"
#include "population.hpp"
#include "basic-ga.hpp"
#include "NSGA-III.hpp"


NSGAIII::NSGAIII(Problem* problem_) : GA{problem_}
{};


NSGAIII::NSGAIII(Problem* problem_, int population_size) : GA{problem_, population_size}
{};

NSGAIII::~NSGAIII(){
    free(fronts);
    free(n_fronts);
    free(ref_dirs);
}

void NSGAIII::run()
{
    std::ofstream outputdat;

    float start = ttime();


    initialize_with_randoms();
    eval_population();

    for (int gen = 0; gen < max_generations; ++gen) {

        gen_parents();
        crossover();
        mutate();
        update_fronts(2*population_size);
        eval_offsprings();
        survival();
    }

    std::cout << "time in second: " << ttime() - start << std::endl;
    std::cout << "no dominated: " << n_fronts[0] << std::endl;



    outputdat.open("data.dat");
    for (int i = 0; i < n_fronts[0]; ++i) {
        for (int j = 0; j < problem->n_objectives; ++j) {
            outputdat << population[i].f[j] << " ";
        }

        outputdat << std::endl;
    }

    outputdat.close();


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
    realmutate();
}


void NSGAIII::realmutate()
{
    int i,j;
    float rnd,delta,indi,deltaq;
    float y,yl,yu,val,xy;

    int popsize = population_size;
    int nvar = problem->n_objectives;
    float** lim_r = problem->bounds;
    float pmut_r = p_m;

    Individual* new_pop_ptr = offsprings;

    for(j = 0;j < popsize;j++)
    {
        for (i = 0;i < nvar; i++)
        {
            rnd = rand01();

            /*For each variable find whether to do mutation or not*/
            if(rnd <= pmut_r)
            {
                y = new_pop_ptr[j].x[i];
                yl = lim_r[i][0];
                yu = lim_r[i][1];

                if(y > yl)
                {
                    /*Calculate delta*/

                    if((y-yl) < (yu-y))
                        delta = (y - yl)/(yu - yl);
                    else
                        delta = (yu - y)/(yu-yl);

                    rnd = rand01(); 

                    indi = 1.0/(dim +1.0);

                    if(rnd <= 0.5)
                    {
                        xy = 1.0-delta;
                        val = 2*rnd+(1-2*rnd)*(pow(xy,(dim+1)));
                        deltaq =  pow(val,indi) - 1.0;
                    }
                    else
                    {
                        xy = 1.0-delta;
                        val = 2.0*(1.0-rnd)+2.0*(rnd-0.5)*(pow(xy,(dim+1)));
                        deltaq = 1.0 - (pow(val,indi));
                    }

                    /*Change the value for the parent */
                    //  *ptr  = *ptr + deltaq*(yu-yl);
                    // Added by Deb (31/10/01)
                    y = y + deltaq * (yu-yl);
                    if (y < yl) y=yl; 
                    if (y > yu) y=yu;
                    new_pop_ptr[j].x[i] = y;
                }
                else // y == yl 
                {
                    xy = rand01();
                    new_pop_ptr[j].x[i] = xy*(yu - yl) + yl;
                }
            }
            //  ptr++;
        }
    }
    return ;
}

void NSGAIII::survival()
{
    if (n_fronts == NULL)
        error("first run update_fronts() method");

    // parent and offspring
    permutate_population(population, fronts, 2*population_size);

    restart_fronts();
    associate_to_niches();
}


void NSGAIII::gen_parents()
{
    if (parent == NULL){
        parent = ivector(population_size);
        for (int i = 0; i < population_size; ++i) {
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



void NSGAIII::associate_to_niches()
{


    int m = problem->n_objectives;
    int K = 0;

    if (ref_dirs == NULL)
        ref_dirs = das_dennis(n_partitions, m, &n_ref_dirs);


    // until last front
    int l = 0, S_size = 0;
    do {
        S_size += n_fronts[++l];
    } while ( S_size < population_size );
    --l;

    // no niching is requiered
    if (S_size == population_size) {
        // printf("No niching is requiered.\n");
        return;
    }


    K = population_size - S_size + n_fronts[l];
    int last_front_size = n_fronts[l];
    int incomplete_pop_size = S_size - n_fronts[l];

    // printf("last_front_size == %d \n", last_front_size);
    // printf("incomplete_pop_size == %d \n", incomplete_pop_size);
    // printf("K = %d\n", K);


    float* denom = fvector(m);

    for (int i = 0; i < m; ++i) {
        denom[i] = nadir[i] - ideal[i];
        if (denom[i] < EPS)
            denom[i] = EPS;
    }


    int parent_childre_size = 2*population_size;
    float* distances_s_to_w = fvector(parent_childre_size);


    // normalize by ideal point and intercepts
    // N = (F - ideal) / denom;
    float** N = fmatrix(parent_childre_size, m);

    for (int i = 0; i < parent_childre_size; ++i) {
        for (int j = 0; j < m; ++j) {
            N[i][j] = (population[i].f[j] - ideal[j]) / denom[j];
        }
    }

    // w in Zr nearest to s in S
    int* pi = ivector(parent_childre_size);
    for (int i = 0; i < parent_childre_size; ++i)
        pi[i] = 0;

    // nich count
    int* rho = ivector(n_ref_dirs);
    for (int i = 0; i < n_ref_dirs; ++i)
        rho[i] = 0;

    // M[i,j] = d'(s,w)
    //float** M = fmatrix(last_front_size, n_ref_dirs);
    float d, d_min;
    for (int i = 0; i < parent_childre_size; ++i) {
        d_min = 1.0 / 0.0;
        // find wj nearest to si
        for (int j = 0; j < n_ref_dirs; ++j) {
            // M[i][j] = norm_point_to_line(N[i], ref_dirs[j], m);
            //M[j][i] = M[i][j];
            d = norm_point_to_line(N[i], ref_dirs[j], m);
            if (d_min > d) {
                d_min = d;
                pi[i] = j;
                distances_s_to_w[i] = d;
            }
        }

        rho[ pi[i] ] += 1;
    }

    niching(K, rho, pi, distances_s_to_w, &fronts[incomplete_pop_size], last_front_size );

    // find those niches where nich count is minimum (say jj )
    // find s in last front such that jj is its corresponding nich
    // --------
    // find those s in last front such that nich count is minimum
    // append such s to P_new and update the niches count.

    free(denom);
    free(N);
    free(rho);
    free(pi);
    free(distances_s_to_w);
    //free(M);
}


void NSGAIII::niching(int K, int* rho, int* pi, float* distances_s_to_w, int* last_front, int last_front_size)
{
    if (K <= 0) {
        return;
    }

    int k = 0;
    int i = 0, j = 0, J_min_size = 0, j_hat;
    int pop_new_size = 0;


    int* pop_new = ivector(K+1);
    int* mask = ivector(n_ref_dirs);
    for (int i = 0; i < n_ref_dirs; ++i)
        mask[i] = i;

    sortperm(rho, mask, n_ref_dirs);

    while( k < K && J_min_size < n_ref_dirs){
        int rho_min = rho[ mask[J_min_size] ];
        // those pho_j such that are equal to the current minimum
        // while (mask[J_min_size] == rho_min) ++J_min_size;
        // IMPORTANT, HERE YOU NEED ADD RANDOM CHOISES
        j_hat = mask[J_min_size];// <-- randint(0, J_min_size);
        ////////////

        float d_min = -1;
        bool I_j_hat_is_empty = true;
        int i_d_min;
        // for each item in I_j_hat
        for (int i = 0; i < last_front_size; ++i) {
            if ( pi[ last_front[i] ] != j_hat )
                continue;

            I_j_hat_is_empty = false;
            // I_j_hat is not empty
            if (rho_min == 0) {
                if (d_min < 0 || d_min > distances_s_to_w[ last_front[i] ]){
                    d_min = distances_s_to_w[ last_front[i] ];
                    i_d_min = i; //last_front[i];
                }
            }else{
                /// HERE YOU NEED ADDING RANDIM CHOISES
                i_d_min = i; //last_front[i];
                break;
            }

        }


        if (!I_j_hat_is_empty) {
            bool is_repeated = false;
            for (int i = 0; i < pop_new_size; ++i) {
                if (pop_new[i] == last_front[i_d_min]) {
                    is_repeated = true;
                    break;
                }
            }

            if (is_repeated) {
                ++J_min_size;
                continue;
            }

            pop_new[pop_new_size++] = last_front[i_d_min];
            rho[pi[last_front[i_d_min]]] += 1;
            ++k;
        }else{
            // here implement to ignore current j_hat
            ++J_min_size;
        }

    }

    if (pop_new_size == 0) {
        return;
    }
    K = pop_new_size;

    int n = population_size - K;
    Individual* P_tmp = (Individual*) malloc(K * sizeof(Individual));
    for (int i = 0; i < K; ++i) {
        P_tmp[i] = population[pop_new[i]];
    }

    for (int i = n; i < population_size; ++i) {
        population[i] = P_tmp[i-n];
    }

    free(mask);
    free(pop_new);


}
