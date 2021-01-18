void error(char* message) {
    printf("ERROR: %s\n", message);
    exit(1);
}

float* fvector(int len) {
    float* v = (float*) malloc(len * sizeof(float));
    if (!v) {
        error("Error allocating memory\n");
    }
    return v;
}


int* ivector(int len) {
    int* v = (int*) malloc(len * sizeof(int));
    if (!v) {
        error("Error allocating memory\n");
    }
    return v;
}

void get_col(float* matrix, float* vec, int* mask, int rows, int cols, int col){
    if (!vec)
        error("Error getting column since vector is empty");

    int i;

    for (i = 0; i < rows; ++i) {
        vec[i] = matrix[mask[i]*cols + col];
    }

    
}

void print_vector(float* v, int len)
{
    int i;

    for (i = 0; i < len; ++i) {
        printf("%2.4g ", v[i]);
    }

    printf("\n");
}



void print_matrix(float* m, int rows, int cols)
{
    int i,j;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%2.4g ", m[i*cols + j]);
        }
        printf("\n");
    }

}
