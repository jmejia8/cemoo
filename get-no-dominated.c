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


void method_two(float* fvalues, int* indices, int n){

    return;
}
