#include "utils.c"
#include "sort.c"


/*
 * a and b are vectors with size k
 * 'i' means a and b are incomparable
 * 'd' a dominates b
 * 'D' b dominates a
 * */
char compare(float* a, float* b, int k)
{
    int i = 0, j;
    while (i < k && a[i] == b[i]) ++i;

    if ( i >= k) return 'e'; // a == b

    if (a[i] < b[i]){

        for (j = i+1; j < k; ++j)
            if (b[j] < a[j]) return 'i'; // a and b are incomparable

        return 'd'; // a dominates b
    }

    for (j = i+1; j < k; ++j) {
        if (a[j] < b[j])
            return 'i'; // a and b are incomparable
    }

    return 'D'; // b dominates a
    
}

// is v dominated by u?
int is_dominated(float* v, float* u, int n){
    int i, flag = 0;
    for (i = 0; i < n; ++i) {
        if (u[i] > v[i]) {
           return 0; 
        } else if (u[i] < v[i]){
            flag = 1;
        }
    }

    return flag;
}


/*
 * Simple method to find the non-dominated set
 * Ref:
 *  Deb, K. (2001). Multi-objective optimization using evolutionary algorithms
 *  (Vol. 16). John Wiley & Sons.
 *  In section 2.4-6 Procedures for Finding a Non-Dominated Set
 *  (approach 1)
 * */
void method_one(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i=0, j, k=0;

    for (i = 0; i < pop_size; ++i) {
        for (j = 0; j < pop_size; ++j) {
            if (i == j) continue;
            if (compare(&fvalues[i*n], &fvalues[j*n], n) == 'D')
               break; 
        }

        // if i is non-dominated by any in population
        if (j >= pop_size) 
            non_dominated[k++] = i;
    }

    *n_non_dominated = k;
}


/*
 * Method to find the non-dominated set
 * Ref:
 *  Deb, K. (2001). Multi-objective optimization using evolutionary algorithms
 *  (Vol. 16). John Wiley & Sons.
 *  In section 2.4-6 Procedures for Finding a Non-Dominated Set
 *  (approach 2)
 * */
void continous_update(float* fvalues, int* non_dominated, int* mask, int pop_size, int len_mask, int* n_non_dominated, int n){
    int i, j, len_p=1;
    int jj, ii;
    char relation;

    // step 1
    non_dominated[0] = mask[0];

    for (i = 1; i < len_mask; ++i) {
        j = 0;
        ii = mask[i];
        while ( j < len_p ) {
            jj = non_dominated[j];
            relation = compare(&fvalues[ii*n], &fvalues[jj*n], n);
            if(relation == 'D'){
                break;
            }

            if (relation == 'd'){
                deleteat(non_dominated, len_p, j);
                jj = non_dominated[j];
                --len_p;
                continue;
            }
            ++j;
        }

        // if i is non-dominated by any in population
        if (j >= len_p) 
            non_dominated[len_p++] = ii;
    }

    *n_non_dominated = len_p;
}


/*
 * Method to find the non-dominated set: Algorithm M2 (inefficient implementation)
 * Ref:  Bentley, J. L., Clarkson, K. L., & Levine, D. B. (1993).
 * Fast linear expected-time algorithms for computing maxima and convex hulls.
 * Algorithmica, 9(2), 168-183.
 * 
 * */
void algorithm_m2(float* fvalues,
                     int* non_dominated,
                     int  pop_size,
                     int* n_non_dominated,
                     int* mask,
                     int len_mask,
                     int n) {

    int i, ii;
    // if it is the first call of function
    // then mask is filled by the all items in fvalues (set s)
    if (!mask) {
        mask = ivector(pop_size);
        for (i = 0; i < pop_size; ++i) mask[i] = i;
    }

    float N = (float) len_mask;

    int ith = (int) floor(0.5 + N*(1.0 - pow(log(N) / N, 1.0 / (float) n )));
    
    float* column = fvector(len_mask);
    float* p = fvector(n);


    // Compute P (step 1)
    for (i = 0; i < n; ++i) {
        get_col(fvalues, column, mask, len_mask, n, i);
        sort(column, len_mask);

        // i-th largest element (revise)
        p[i] = column[ len_mask - ith];
    }

    int len_C = 0;
    char relation;

    int len_mask_new = 0;
    int* mask_new = ivector(len_mask);

    // step 2
    for (i = 0; i < len_mask; ++i) {
        ii = mask[i];
        relation = compare(&fvalues[ii*n], p, n);

        if (relation == 'd'){ // row dominates p?
            // increment size of C
            ++len_C;
        }else if (relation != 'i') // are row and p no incomparable?
            continue;
        // B union C (in step 4)
        mask_new[len_mask_new++] = ii;
    }


    // step 3
    if (len_C == 0) {
        continous_update(fvalues, non_dominated, mask, pop_size, len_mask, n_non_dominated, n);
        return;
    }

    if (len_mask_new == len_mask) {
        continous_update(fvalues, non_dominated, mask, pop_size, len_mask, n_non_dominated, n);
        return;
    }

    // step 4
    *n_non_dominated = len_mask_new;
    algorithm_m2(fvalues, non_dominated, pop_size, n_non_dominated, mask_new, len_mask_new, n);
}


/*
 * Method to find the non-dominated set: Algorithm M3
 * Ref:  Bentley, J. L., Clarkson, K. L., & Levine, D. B. (1993).
 * Fast linear expected-time algorithms for computing maxima and convex hulls.
 * Algorithmica, 9(2), 168-183.
 * 
 * */
void algorithm_M3(float* fvalues, int* non_dominated, int* mask, int pop_size, int len_mask, int* n_non_dominated, int n){
    int i, j, len_p=1;
    int jj, ii;
    char relation;

    // step 1
    non_dominated[0] = mask[0];

    for (i = 1; i < len_mask; ++i) {
        j = 0;
        ii = mask[i];
        while ( j < len_p ) {
            jj = non_dominated[j];
            relation = compare(&fvalues[ii*n], &fvalues[jj*n], n);

            // j dominates i?
            if(relation == 'D'){
                move_to_front(non_dominated, j, len_p);
                j = len_p + 1;
            // i dominates j?
            } else if (relation == 'd'){
                deleteat(non_dominated, len_p, j);
                jj = non_dominated[j];
                --len_p;
            // are solution i and j equal?
            } else if (relation == 'e'){
                j = len_p + 1;
            }else // ok, those are no comparable
                ++j;

        }

        if (j == len_p) 
            non_dominated[len_p++] = ii;
    }

    *n_non_dominated = len_p;
}



/*
 * Get the non_dominated set and save it into non_dominated with size n_non_dominated
 * by using method = 1,2 or, 3
 * fvalues contains the objective function values in a matrix (by rows) with size pop_size x n
 * */
void get_non_dominated(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n, int method) {
    int* mask = ivector(pop_size);
    int i;
    for (i = 0; i < pop_size; ++i) mask[i] = i;

    switch (method) {
        case 1:
            method_one(fvalues, non_dominated, pop_size, n_non_dominated, n);
            break;
        case 2:
            continous_update(fvalues, non_dominated, mask, pop_size, pop_size, n_non_dominated, n);
            break;
        case 3:
            algorithm_M3(fvalues, non_dominated, mask, pop_size, pop_size, n_non_dominated, n);
            break;
        default:
            error("method should be set 1, 2 or 3 (3 is in general faster)");
            
    }
}

/*
 *
 * fronts = {i | i in fronts}
 * n_fronts[i] size of fronts[i]
 * 
 * */
void get_fronts(float* fvalues, int* fronts, int* n_fronts, int pop_size, int n)
{

    int i, j, ii, jj;
    char relation;

    // step 1
    int is_dominating[pop_size][pop_size], n_dominated[pop_size];
    int n_current_front;
    // float ranked[pop_size];
    int n_ranked = 0;
    
    for (i = 0; i < pop_size; ++i) {
        n_dominated[i] = 0;
        n_fronts[i] = 0;

    }

    for (i = 0; i < pop_size; ++i) {
        for (j = i+1; j < pop_size; ++j) {
            relation = compare(&fvalues[i*n], &fvalues[j*n], n);
            // j domiates i?
            if(relation == 'D'){
                is_dominating[j][n_dominated[j]] = i;
                n_dominated[i] += 1;
            // i domiates j?
            }else if (relation == 'd'){
                is_dominating[i][n_dominated[i]] = j;
                n_dominated[j] += 1;
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

    // while not all solutions are assigned to a pareto front
    while(n_ranked < pop_size) {
        // for each individual in the current front
        for (ii = 0; ii < n_fronts[ n_current_front ]; ++ii) {
            i = current_front[ii];

            // all solutions that are dominated by this individual
            for (jj = 0; jj < n_dominated[i]; ++jj) {
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

        ++n_current_front;
        // move to next front
        current_front = &fronts[ n_ranked - n_fronts[ n_current_front ] ];
    }

}



/*
 * Adapted from:
 * https://github.com/msu-coinlab/pymoo/blob/master/pymoo/util/nds/fast_non_dominated_sort.py
 *
 * */
void fast_non_dominated(float* fvalues, int* sort, int* rank, int pop_size, int n) {
    int fronts[pop_size], n_fronts[pop_size], i;

    for (i = 0; i < pop_size; ++i) {
        fronts[i] = 0;
        n_fronts[i] = 0;
    }

    get_fronts(fvalues, fronts, n_fronts, pop_size, n);

    for (i = 0; i < n_fronts[i]; ++i) {
        printf("%d ", fronts[i]);
    }
    printf("\n");

}



