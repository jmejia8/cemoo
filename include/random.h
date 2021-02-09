#ifndef RANDOM_H
#define RANDOM_H


void fill_random(double a, double b, double* array, int size);
double rand01();
void fill_population(double* positions, int N, int n, double* bounds[]);
int randint(int a, int b);
void randperm(int* values, int len);


#endif

