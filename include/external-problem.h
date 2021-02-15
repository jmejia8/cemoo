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


void ZCAT20(double* x, double* F, int n, int M)
{
    int level = 2, i, j;
    bool bias = false;

    double alpha[M];
    int m;

    double y[n], *y_II = &y[m];
    for (i = 0; i < n; ++i) {
        y[i] = (x[i] - ( ( (double) i + 1) / 2.0 )) / ( (double) i + 1);
    }

    if ( (0.1 <= y[0] && y[0] <= 0.4 ) || (0.6 <= y[0] && y[0] <= 0.9 ) ) {
        m = 1;
    }else
        m = M-1;

    for (i = 0; i < M - 1; ++i) {
        if (m == 1)
            alpha[i] = y[0];
        else
            alpha[i] = y[i];
    }

    alpha[M-1] = pow( (double) M, 2.0);

    if (m == 1) {
        alpha[M-1] *= (pow(0.5 - y[0], 5) + pow(0.5, 5)) / (2.0 * pow(0.5, 5));
    }else{
        double s = 0.0;
        for (int i = 0; i < M-1; ++i) {
            s += (pow(0.5 - y[i], 5) );
        }
        alpha[M-1] *= s / (2.0 * ( (double) M - 1) * pow(0.5, 5)) + 0.5 ;
    }
    // alpha seems ok

    double g[n - m], theta;
    for (j = 0; j < n - m; ++j) {
        g[i] = 0.0;//1.0 / ((double m)) * 
        for (i = 0; i < m; ++i) {
            theta = 2.0*M_PI * (  ( (double)( j )) / (double) n );
            g[i] += pow( cos( M_PI * y[i] + theta ), 2);
        }
        g[i] /= (double) m;
    }

    double beta[M], maxj, wj;
    for (i = 0; i < M; ++i) {
        maxj = -1.0;
        for (j = m; j < n; ++j) {
            if ((j - m - i) % M != 0) 
                continue;
            // wj = x[j];
            // differs from paper (supplementary material)
            wj = y[j] - g[j - m];
            maxj = fabs(wj) > maxj ? fabs(wj) : maxj;
        }

        beta[i] = 10.0*pow((double) i+1, 2) * maxj;
    }

    for (i = 0; i < M; ++i) {
        F[i] = alpha[i] + beta[i];
    }

}

void objective_function(double* x, double* F, int n, int m){
    ZCAT20(x, F, n, m);
}

#endif
