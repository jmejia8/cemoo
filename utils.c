void error(char* message) {
    printf("%s\n", message);
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

