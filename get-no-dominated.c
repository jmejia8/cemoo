#include "utils.c"
#include "sort.c"

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


int is_non_dominated(float* sol_a, float* sol_b, int n){
    return !is_dominated(sol_a, sol_b, n);
}

void method_one(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i=0, j, k=0;

    for (i = 0; i < pop_size; ++i) {
        for (j = 0; j < pop_size; ++j) {
            if (i == j) continue;
            if (is_dominated(&fvalues[i*n], &fvalues[j*n], n))
               break; 
        }

        // if i is non-dominated by any in population
        if (j >= pop_size) 
            non_dominated[k++] = i;
    }

    *n_non_dominated = k;
}

void deleteat(int* array, int len, int i) {
    int j;

    for (j = i; j < len-1; ++j) {
        array[j] = array[j+1];
    }
    
}

void continous_update(float* fvalues, int* non_dominated, int* mask, int pop_size, int len_mask, int* n_non_dominated, int n){
    int i, j, len_p=1;
    int jj, ii;

    // step 1
    non_dominated[0] = mask[0];

    for (i = 1; i < len_mask; ++i) {
        j = 0;
        ii = mask[i];
        while ( j < len_p ) {
            jj = non_dominated[j];
            if(is_dominated(&fvalues[ii*n], &fvalues[jj*n], n)){
                break;
            }

            if (is_dominated(&fvalues[jj*n], &fvalues[ii*n], n)){
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

void method_two(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i;
    int* mask = ivector(pop_size);
    for (i = 0; i < pop_size; ++i) mask[i] = i;
    continous_update(fvalues, non_dominated, mask, pop_size, pop_size, n_non_dominated, n);
}
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

void bentleys_method(float* fvalues,
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
    bentleys_method(fvalues, non_dominated, pop_size, n_non_dominated, mask_new, len_mask_new, n);
}

void method_three(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n) {
    int* mask = ivector(pop_size);
    int i;
    for (i = 0; i < pop_size; ++i) mask[i] = i;
    bentleys_method(fvalues, non_dominated, pop_size, n_non_dominated, mask, pop_size, n);
}

