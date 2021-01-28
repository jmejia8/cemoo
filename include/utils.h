#ifndef UTILS_H
#define UTILS_H

// #define min(a,b) (a < b ? a : b)
// #define max(a,b) (a > b ? a : b)

/*
 * Print error message and exit the program.
 * */
void error(const char* ) ;

/*
 * creates a vector of floats with size len
 * */
float* fvector(int ) ;

/*
 * creates a vector of integers with size len
 * */
int* ivector(int ) ;


int** imatrix(int , int ) ;


float** fmatrix(int rows, int cols) ;
/*
 * get column col via vec in a matrix 
 * */
void get_col(float* matrix, float* vec, int* mask, int rows, int cols, int col);

void print_vector(float* v, int len);



/*
 * print matrix with size rows x cols
 * */
void print_matrix(float* m, int rows, int cols);

/*
 * delete item array[i] from array with size len.
 * */
void deleteat(int* array, int len, int i) ;



/*
 * Move the j-th item in array to the first array[0]
 * */
void move_to_front(int* array, int j, int n);


int argmin(float* array, int len);

float minimum(float* array, int len);

void fill_ideal(float* ideal, float* fvalues, int N, int m);

float ttime();



char compare(float* a, float* b, int k);

#endif
