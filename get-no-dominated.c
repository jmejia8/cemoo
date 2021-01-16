// is a dominated by b?
int is_dominated(float* sol_a, float* sol_b, int n){
    int i;
    for (i = 0; i < n; ++i) {
        if (sol_a[i] > sol_b[i]) {
           return 1; 
        }
    }

    return 0;
}


int is_non_dominated(float* sol_a, float* sol_b, int n){
    return !is_dominated(sol_a, sol_b, n);
}

void method_one(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i=0, j, k=0;

    while(i < n){
        for (j = 0; j < pop_size; ++j) {
            if (i == j) continue;
            if (is_dominated(&fvalues[i], &fvalues[j], n))
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
