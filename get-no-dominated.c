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


void method_one(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i=0, j, k=0;
    int l;


    printf("Paso 1: $i = %d$. $P' = \\emptyset$\n\n", i+1);
    for (i = 0; i < pop_size; ++i) {
        for (j = 0; j < pop_size; ++j) {
            if (i == j) continue;
            printf("Paso 2: Para $j = %d$. ", j+1);
            if (compare(&fvalues[i*n], &fvalues[j*n], n) == 'D'){
                printf("Como $j = %d$ domina a $i = %d$, ir a Paso 4\n\n", j+1, i+1);
                break; 
            }
            printf("Como $j = %d$ no domina a $i = %d$, ir a Paso 3.\n\n", j+1, i+1);
            if (j < pop_size-1)
            printf("Paso 3: Como $j = %d \\leq N = %d$, ir a Paso 2.\n\n",j+1, pop_size);
        }

        // if i is non-dominated by any in population
        if (j >= pop_size) {
            printf("Paso 3: Como $j = N = %d$, $P' = P' \\union \\{%d\\}$. ", j,i+1 );
            non_dominated[k++] = i;
            printf("Así, $P' = \\{");
            for (l = 0; l < k; ++l) 
                printf("%d, ", non_dominated[l] +1 );
            printf("\\}$. Ir a paso 4.\n\n");
        }

        printf("Paso 4: Incrementando $i$ a $i+1=%d$.\n\n", i+2 );
    }

    printf("Paso 4: Como $i\\geq N$, entonces ");
    printf("$P' = \\{");
    for (l = 0; l < k; ++l) 
        printf("%d, ", non_dominated[l] +1 );
    printf("\\}$ es el conjunto no dominado.\n\n");

    *n_non_dominated = k;
}


void continous_update(float* fvalues, int* non_dominated, int* mask, int pop_size, int len_mask, int* n_non_dominated, int n){
    int i, j, len_p=1;
    int jj, ii;
    char relation;
    int l;

    // step 1
    non_dominated[0] = mask[0];
    printf("Paso 1: $P' = \\{ %d \\}, \\ i = 2$.  \n\n", non_dominated[0] + 1);

    for (i = 1; i < len_mask; ++i) {
        j = 0;
        printf("Paso 2: Hacer $j = 1$ . \n \n");
        ii = mask[i];
        while ( j < len_p ) {
            jj = non_dominated[j];
            printf("Paso 3: Comparar solución $i=%d$ con la $j=%d$ de $P'$.\n\n", ii+1, jj+1);
            relation = compare(&fvalues[ii*n], &fvalues[jj*n], n);
            if(relation == 'D'){
                printf("Paso 4: Como el miembro $j=%d$ de $P'$ domina a $i=%d$.", jj+1, ii+1 );
                if(i<len_mask-1)
                    printf("Incrementar i en uno e ir al Paso 2. \n\n");
                else
                printf(" Incrementar $i=%d$ en uno e ir al Paso 5.\n\n", ii+1);
                break;
            }

            if (relation == 'd'){
                printf("Paso 4: Como $i = %d$ domina a $j=%d$, entonces borrar el elemento %d de $P'$. ", ii+1, jj+1, jj+1);
                deleteat(non_dominated, len_p, j);
                jj = non_dominated[j];
                --len_p;

                printf("Así, $P' = \\{");
                for (l = 0; l < len_p; ++l) 
                    printf("%d, ", non_dominated[l] +1 );
                printf("\\}$. \n\n");
                continue;
            }
            if (j<len_p-1) {
                printf("Paso 4: Como $i$ no domina a $j$ y $j=%d < |P'| = %d$, entonces incrementar $j$ en uno e ir al Paso 3.\n\n", jj+1, len_p);
            }else
                printf("Paso 4: Como $i$ no domina a $j$ y $j= |P'| = %d$, entonces ir al Paso 5.\n\n", len_p);
            ++j;
        }

        // if i is non-dominated by any in population
        if (j >= len_p){
            //printf("Paso 4: Como $j = %d \\geq |P'|=%d$, ir a Paso 5.\n\n", jj+1, len_p);
            printf("Paso 5: Insertar $i = %d$ en $P'$. ", ii+1);
            non_dominated[len_p++] = ii;

            printf("Así, $P' = \\{");
            for (l = 0; l < len_p; ++l) 
                printf("%d, ", non_dominated[l] +1 );
            printf("\\}$. ");

            if (i<len_mask-1) {
                printf("Incrementar $i$ en uno e ir al Paso 2.\n\n");
            }
        }
    }

    printf("Paso 5: Como $i\\geq N $, entonces el conjunto no dominado es:\n");
    printf("$P' = \\{");
    for (l = 0; l < len_p; ++l) 
        printf("%d, ", non_dominated[l] +1 );
    printf("\\}$\n");


    *n_non_dominated = len_p;
}

void method_two(float* fvalues, int* non_dominated, int pop_size, int* n_non_dominated, int n){
    int i;
    int* mask = ivector(pop_size);
    for (i = 0; i < pop_size; ++i) mask[i] = i;
    continous_update(fvalues, non_dominated, mask, pop_size, pop_size, n_non_dominated, n);
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

