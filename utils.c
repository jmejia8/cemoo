/*
 * Print error message and exit the program.
 * */
void error(char* message) {
    printf("ERROR: %s\n", message);
    exit(1);
}


/*
 * creates a vector of floats with size len
 * */
float* fvector(int len) {
    float* v = (float*) malloc(len * sizeof(float));
    if (!v) {
        error("Error allocating memory\n");
    }
    return v;
}


/*
 * creates a vector of integers with size len
 * */
int* ivector(int len) {
    int* v = (int*) malloc(len * sizeof(int));
    if (!v) {
        error("Error allocating memory\n");
    }
    return v;
}


/*
 * get column col via vec in a matrix 
 * */
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
        printf("%2.04f ", v[i]);
    }

    printf("\n");
}



/*
 * print matrix with size rows x cols
 * */
void print_matrix(float* m, int rows, int cols)
{
    int i,j;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%2.04f ", m[i*cols + j]);
        }
        printf("\n");
    }

}


/*
 * delete item array[i] from array with size len.
 * */
void deleteat(int* array, int len, int i) {
    int j;

    for (j = i; j < len-1; ++j) {
        array[j] = array[j+1];
    }
    
}



/*
 * Move the j-th item in array to the first array[0]
 * */
void move_to_front(int* array, int j, int n)
{
    if (j == 0 || j >= n )
        return;

    int i;
    int v = array[j];

    for (i = j; i >= 0; --i)
        array[i] = array[i-1];

    array[0] = v;

}


int argmin(float* array, int len){
    int i, i_min = 0;
    float min = array[0];

    for (i = 1; i < len; ++i) {
        if (min > array[i]) {
            min = array[i];
            i_min = i;
        }
    }

    return i_min;

}

float minimum(float array, int len)
{
    return array[ argmin(array, len) ];

}

void fill_ideal(float* ideal, float* fvalues, int N, int m)
{
    int i, j;
    float f; // auxiliar function
    for (j = 0; j < m; ++j) {

        // assume first vector in fvalues is the ideal
        ideal[j] = fvalues[j];
        for (i = 1; i < N; ++i) {
            f = fvalues[i*m + j];
            if (ideal[j] > f) ideal[j] = f;
        }
    }
}
