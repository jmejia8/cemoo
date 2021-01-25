/*
 * Read a file named fname and return the matrix as a 1D vector
 * the number of rows and cols are saved via pop_size and n, respectively.
 * */
float* read_txt(char* fname, int *pop_size, int* n){
    FILE *file;
    float *fvals;
    
    file = fopen(fname, "r");

    // deal with errors
    if (!file) {
        printf("Error reading file %s.\n", fname);
        exit(1);
    }
    
    
    int i, j, N, m;
    float f;

    fscanf(file, "%d %d", &N, &m);

    fvals = (float*) malloc(m * N * sizeof(float));

    for (i = 0; i < N; ++i) {
        for (j = 0; j < m; ++j) {
            fscanf(file, "%f", &f );
            fvals[i*m + j] = f;
        }
    }

    *pop_size = N;
    *n = m;

    fclose(file);

    return fvals;
}


void write_txt(float* array, int N, int m, char* fname) {
    FILE *file;
    
    file = fopen(fname, "w");

    // deal with errors
    if (!file) {
        printf("Error creating file %s.\n", fname);
        exit(1);
    }
    
    
    int i, j;

    fprintf(file, "%d %d\n", N, m);

    for (i = 0; i < N; ++i) {
        for (j = 0; j < m; ++j) {
            fprintf(file, "%f ", array[i*m + j] );
        }
        fprintf(file, "\n");
    }

    fclose(file);

}

void iwrite_txt(int* array, int N, int m, char* fname) {
    FILE *file;
    
    file = fopen(fname, "w");

    // deal with errors
    if (!file) {
        printf("Error creating file %s.\n", fname);
        exit(1);
    }
    
    
    int i, j;

    fprintf(file, "%d %d\n", N, m);

    for (i = 0; i < N; ++i) {
        for (j = 0; j < m; ++j) {
            fprintf(file, "%d ", array[i*m + j] );
        }
        fprintf(file, "\n");
    }

    fclose(file);

}
