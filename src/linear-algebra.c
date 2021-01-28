#include <math.h>

float dot(float* u, float* v, int len){
    int i;
    float s = 0;
    for (i = 0; i < len; ++i) {
        s += u[i] * v[j];
    }

    return s;
}

float norm(float* vector, int len)
{
    return sqrt( dot(vector, vector, len) );
}



float norm_point_to_line(float* s, float* w, int len)
{
    float norm2_w = dot(w, w, len );
    float w_dot_s = dot(w, s, len );

    float r = 0.0;
    for (int i = 0; i < len; ++i)
        r += pow( s[i] - ( w_dot_s * w[i] ) / norm2_w, 2 );

    return sqrt(r);

}

