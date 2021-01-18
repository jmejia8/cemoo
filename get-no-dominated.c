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

void method_two(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i, j, len_p=1;
    int jj;

    // step 1
    non_dominated[0] = 0;

    for (i = 1; i < pop_size; ++i) {
        j = 0;
        while ( j < len_p ) {
            jj = non_dominated[j];
            if(is_dominated(&fvalues[i*n], &fvalues[jj*n], n)){
                break;
            }

            if (is_dominated(&fvalues[jj*n], &fvalues[i*n], n)){
                deleteat(non_dominated, len_p, j);
                jj = non_dominated[j];
                --len_p;
                continue;
            }
            ++j;
        }

        // if i is non-dominated by any in population
        if (j >= len_p) 
            non_dominated[len_p++] = i;
    }

    *n_non_dominated = len_p;
}

void bentleys_method(float* fvalues,
                     int* non_dominated,
                     int  pop_size,
                     int* n_non_dominated,
                     int* mask_comparison,
                     int n) {

    if (!mask_comparison) {
        mask_comparison = ivector(pop_size);
    }

    float N = (float) pop_size;

    int ith = (int) floor(N*(1.0 - pow(log(N) / N, 1.0 / (float) n )));
    
    float* column = fvector(pop_size);
    float* p = fvector(n);


    // Compute P (step 1)
    int i, ii;
    for (i = 0; i < n; ++i) {
        get_col(fvalues, column, pop_size, n, i);
        sort(column, pop_size);

        // i-th largest element (revise)
        p[i] = column[ pop_size - ith - 1];
    }

    int* C = ivector(pop_size); int len_C;
    int* B = ivector(pop_size); int len_B;
    char relation;

    // step 2
    for (i = 0; i < pop_size; ++i) {
        relation = compare(fvalues[i*n], p, n);

        if (relation == 'd'){ // row dominates p?
            C[len_C++] = i;
        else if (relation == 'i') // are row and p incomparable?
            B[len_B++] = i;
        else
            continue;
        mask_comparison[len_mask++] = i;
    }

    // step 3
    if (len_C == 0) {
        method_two(fvalues, non_dominated, pop_size, n_non_dominated, n);
        return;
    }

    // step 4
    



}

void method_three(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n) {
    int* mask_comparison = ivector(pop_size);
    bentleys_method(fvalues, non_dominated, pop_size, n_non_dominated, mask_comparison, n);
}

