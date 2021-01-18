#include "utils.h"

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

void bentlays_method(float* fvalues,
                     int* non_dominated,
                     int  pop_size,
                     int* n_non_dominated,
                     int* mask_comparison,
                     int n) {

    if (!mask_non_dominated) {
        mask_comparison = ivector(pop_size);
    }

    float* p = fvector(n);

}

void method_three(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n) {
    *n_non_dominated = len_p;
}

