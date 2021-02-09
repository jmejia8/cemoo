#include <stdlib.h>
#include <time.h>

void fill_random(double a, double b, double* array, int size)
{
    double l = b-a;
    int i;

    for (i = 0; i < size; ++i) {
        array[i] = a + l * (double) rand() / (double)RAND_MAX ;
    }
    
}


double rand01()
{
    return (double) rand() / (double)RAND_MAX;
}



void fill_population(double* positions, int N, int n, double* bounds[])
{
    int i, j;
    double l;
    for (j = 0; j < n; ++j) {
        l = bounds[j][1] - bounds[j][0];
        for (i = 0; i < N; ++i) {
            positions[i*n + j] = bounds[j][0] + l*rand01();
        }
    }

}

int randint(int a, int b)
{
    return a + rand() % (b-a);
}

void randperm(int* values, int len)
{
    int j, tmp;
    for (int i = 0; i < len; ++i) {
        j = randint(0, len-i);
        tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
    }
}

