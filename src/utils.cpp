#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Print error message and exit the program.
 * */
void error(const char* message) {
    printf("\033[31mERROR: %s\033[0m\n", message);
    exit(1);
}


/*
 * creates a vector of doubles with size len
 * */
double* fvector(int len) {
    double* v = (double*) malloc(len * sizeof(double));
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



int** imatrix(int rows, int cols) {
    int** matrix = (int**) malloc(rows * sizeof(int*));
    if (!matrix) {
        error("Error allocating memory\n");
    }

    int i;
    for (i = 0; i < rows; ++i) {
        matrix[i] = ivector(cols);
    }

    return matrix;
}



double** fmatrix(int rows, int cols) {
    double** matrix = (double**) malloc(rows * sizeof(int*));
    if (!matrix) {
        error("Error allocating memory\n");
    }

    int i;
    for (i = 0; i < rows; ++i) {
        matrix[i] = fvector(cols);
    }

    return matrix;
}


/*
 * get column col via vec in a matrix 
 * */
void get_col(double* matrix, double* vec, int* mask, int rows, int cols, int col){
    if (!vec)
        error("Error getting column since vector is empty");

    int i;

    for (i = 0; i < rows; ++i) {
        vec[i] = matrix[mask[i]*cols + col];
    }

    
}

void print_vector(double* v, int len)
{
    int i;

    for (i = 0; i < len; ++i) {
        printf("%+2.04f ", v[i]);
    }

    printf("\n");
}



/*
 * print matrix with size rows x cols
 * */
void print_matrix(double* m, int rows, int cols)
{
    int i,j;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%+2.04f ", m[i*cols + j]);
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


int argmin(double* array, int len){
    int i, i_min = 0;
    double min = array[0];

    for (i = 1; i < len; ++i) {
        if (min > array[i]) {
            min = array[i];
            i_min = i;
        }
    }

    return i_min;

}

double minimum(double* array, int len)
{
    return array[ argmin(array, len) ];

}

void fill_ideal(double* ideal, double* fvalues, int N, int m)
{
    int i, j;
    double f; // auxiliar function
    for (j = 0; j < m; ++j) {

        // assume first vector in fvalues is the ideal
        ideal[j] = fvalues[j];
        for (i = 1; i < N; ++i) {
            f = fvalues[i*m + j];
            if (ideal[j] > f) ideal[j] = f;
        }
    }

}

double ttime(){
    return ((double) clock() ) / CLOCKS_PER_SEC;
}



/*
 * a and b are vectors with size k
 * 'i' means a and b are incomparable
 * 'd' a dominates b
 * 'D' b dominates a
 * */
char compare(double* a, double* b, int k)
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


void update_ideal(double* ideal, double* f, int len)
{
    for (int i = 0; i < len; ++i) {
        if (ideal[i] > f[i])
            ideal[i] = f[i];
    }
}


void update_nadir(double* nadir, double* f, int len)
{
    for (int i = 0; i < len; ++i) {
        if (nadir[i] < f[i])
            nadir[i] = f[i];
    }
}


int factorial(int m, int n)
{
    int v = 1;
    for (int i = m; i <= n; ++i)
        v *= i;
    return v;
}

int nCr(int n, int r)
{
    return factorial(r + 1, n) / factorial(1, n-r);
}


void das_dennis_recursion(double** ref_dirs, double* ref_dir,int n_partitions,int beta,int depth, int n_dim, int* len)
{
    if (depth == n_dim - 1) {
        ref_dir[depth] = (double) beta / (1.0 * n_partitions);
        for (int i = 0; i < n_dim; ++i){
            ref_dirs[*len][i] = ref_dir[i];
        }

        *len = *len + 1;
        return;
    }

    double* ref_dir_copy = fvector(n_dim);

    for (int i = 0; i < beta + 1; ++i) {
        ref_dir[depth] = 1.0 * (double) i / (1.0 * n_partitions);

        // copy ref_dir
        for (int j = 0; j < n_dim; ++j) ref_dir_copy[j] = ref_dir[j];

        das_dennis_recursion(ref_dirs, ref_dir_copy, n_partitions, beta - i, depth + 1, n_dim, len);
    }

    free(ref_dir_copy);
}



double** das_dennis(int n_partitions, int n_dim, int* len)
{

    int n = nCr(n_dim + n_partitions-1, n_partitions);
    *len = 0;

    double** ref_dirs = fmatrix(n, n_dim);

    if (n_partitions == 0) {
        for (int i = 0; i < n_dim; ++i) {
            ref_dirs[0][i] = 1.0 / (double) n_dim;
        }
        *len = 1;
        return ref_dirs;
    }

    
    double* ref_dir = fvector(n_dim);
    das_dennis_recursion(ref_dirs, ref_dir, n_partitions, n_partitions, 0, n_dim, len);

    //*len = n;

    free(ref_dir);


    return ref_dirs;


}



double** gen_ref_points(int n_inside, int n_boudary, int n_dim, int* len)
{
    int len_inside, len_boudary;
    double** refpoints_boudary = das_dennis(n_boudary, n_dim, &len_boudary);

    len[0] = len_boudary;
    if (n_inside <= 0)
        return refpoints_boudary;

    double** refpoints_inside = das_dennis(n_inside, n_dim, &len_inside);

    double center = 1.0/n_dim;
    for (int i = 0; i < len_inside; ++i) {
        for (int j = 0; j < n_dim; ++j)
            refpoints_inside[i][j] = (center + refpoints_inside[i][j])/2;
    }

    len[0] += len_inside;
    double** refpoints = (double**) malloc( sizeof(double*) * len[0] ) ;

    for (int i = 0; i < len_boudary; ++i) 
        refpoints[i] = refpoints_boudary[i];
    
    for (int i = 0; i < len_inside; ++i) 
        refpoints[len_boudary + i] = refpoints_inside[i];

    return refpoints;

}


void sortperm(int *A, int* mask, int len)
{
  if (len < 2) return;
 
  int pivot = A[ mask[ len / 2]];
 
  int i, j;
  for (i = 0, j = len - 1; ; i++, j--) {

    while (A[mask[i]] < pivot) i++;
    while (A[mask[j]] > pivot) j--;
 
    if (i >= j) break;
 

    int temp     = mask[i];
    mask[i]  = mask[j];
    mask[j]  = temp;
  }
 
  sortperm(A, mask, i);
  sortperm(A , mask + i, len - i);
}
