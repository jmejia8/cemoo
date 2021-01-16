float* read_txt(char* fname, int *pop_size, int* n){
    FILE *file;
    float *fvals;
    
    file = fopen(fname, "r");

    // deal with errors
    if (!file) {
        printf("Error reading file %s.", fname);
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
