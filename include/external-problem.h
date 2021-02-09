#ifndef EXTERNAL_PROBLEM
#define EXTERNAL_PROBLEM

#include <math.h>

void DTLZ2(double* x, double* F, int n, int m)
{
    int i,j, k = 10;
    double g = 0.0;

    for (i = m-1; i < n; ++i)
        g += pow(x[i] - 0.5, 2);

    for (i = 0; i < m; ++i) {
        F[i] = (1.0 + g);

        for (j = 0; j < m-i-1; ++j) {
            F[i] *= cos(x[j] * M_PI / 2.0 );
        }
        
        if (i > 0) {
            F[i] *=  sin(x[m-i-1] * M_PI / 2.0 );
        }

    }
    
}

void tmp(double* x, double* F, int n, int m)
{
    
}



void objective_function(double* x, double* F, int n, int m){
    DTLZ2(x, F, n, m);
}

#endif
