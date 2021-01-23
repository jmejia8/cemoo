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

