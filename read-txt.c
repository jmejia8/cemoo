void read_txt(char* fname, float *fvals, int *pop_size, int* n){
    FILE *file;
    
    file = fopen(fname, "r");

    // deal with errors
    if (!file) {
        printf("Error reading file %s.", fname);
        exit(1);
        return;
    }
    
    
    int i, j, N, m;
    float f;

    fscanf(file, "%d %d", &N, &m);
    printf("N, m = %d %d\n", N, m);

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

    return;
}
