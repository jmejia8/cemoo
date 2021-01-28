#ifndef RANDOM_H
#define RANDOM_H


void fill_random(float a, float b, float* array, int size);
float rand01();
void fill_population(float* positions, int N, int n, float* bounds[]);
int randint(int a, int b);
void randperm(int* values, int len);


#endif

