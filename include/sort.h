// adapted from:
//https://rosettacode.org/wiki/Sorting_algorithms/Quicksort 
 
void quicksort(float *A, int len) {
  if (len < 2) return;
 
  float pivot = A[len / 2];
 
  int i, j;
  for (i = 0, j = len - 1; ; i++, j--) {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;
 
    if (i >= j) break;
 
    float temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;
  }
 
  quicksort(A, i);
  quicksort(A + i, len - i);
}

void sort(float* A, int len) {
    quicksort(A, len);
}
