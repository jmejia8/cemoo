#ifndef UTILS_H
#define UTILS_H

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

#define EPS 1e-12 

// #define min(a,b) (a < b ? a : b)
// #define max(a,b) (a > b ? a : b)

/*
 * Print error message and exit the program.
 * */
void error(const char* ) ;

/*
 * creates a vector of doubles with size len
 * */
double* fvector(int ) ;

/*
 * creates a vector of integers with size len
 * */
int* ivector(int ) ;


int** imatrix(int , int ) ;


double** fmatrix(int rows, int cols) ;
/*
 * get column col via vec in a matrix 
 * */
void get_col(double* matrix, double* vec, int* mask, int rows, int cols, int col);

void print_vector(double* v, int len);



/*
 * print matrix with size rows x cols
 * */
void print_matrix(double* m, int rows, int cols);

/*
 * delete item array[i] from array with size len.
 * */
void deleteat(int* array, int len, int i) ;



/*
 * Move the j-th item in array to the first array[0]
 * */
void move_to_front(int* array, int j, int n);


int argmin(double* array, int len);

double minimum(double* array, int len);

void fill_ideal(double* ideal, double* fvalues, int N, int m);

double ttime();



char compare(double* a, double* b, int k);

double norm_point_to_line(double* s, double* w, int len);


void update_nadir(double* nadir, double* f, int len);
void update_ideal(double* ideal, double* f, int len);


int factorial(int m, int n);
int nCr(int n, int r);
void das_dennis_recursion(double** ref_dirs, double* ref_dir,int n_partitions,int beta,int depth, int n_dim, int* len);
double** das_dennis(int n_partitions, int n_dim, int* len);



void sortperm(int *A, int* mask, int len);



#endif
