void fill_random(float a, float b, float* array, int size)
{
    float l = b-a;
    int i;

    for (i = 0; i < size; ++i) {
        array[i] = a + l * (float)rand() / (float)RAND_MAX ;
    }
    
}


float rand01(){
    return (float)rand() / (float)RAND_MAX;
}

