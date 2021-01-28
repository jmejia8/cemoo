#include <stdlib.h>
#include <time.h>

void fill_random(float a, float b, float* array, int size)
{
    float l = b-a;
    int i;

    for (i = 0; i < size; ++i) {
        array[i] = a + l * (float)rand() / (float)RAND_MAX ;
    }
    
}


float rand01()
{
    return (float)rand() / (float)RAND_MAX;
}



void fill_population(float* positions, int N, int n, float* bounds[])
{
    int i, j;
    float l;
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

