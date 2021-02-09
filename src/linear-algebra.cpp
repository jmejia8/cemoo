#include <math.h>

double dot(double* u, double* v, int len){
    int i;
    double s = 0;
    for (i = 0; i < len; ++i) {
        s += u[i] * v[i];
    }

    return s;
}

double norm(double* vector, int len)
{
    return sqrt( dot(vector, vector, len) );
}



double norm_point_to_line(double* s, double* w, int len)
{
    double norm2_w = dot(w, w, len );
    double w_dot_s = dot(w, s, len );

    double r = 0.0;
    for (int i = 0; i < len; ++i)
        r += pow( s[i] - ( w_dot_s * w[i] ) / norm2_w, 2 );

    return sqrt(r);

}

