#include <stdio.h>
#include <stdlib.h>

static void swap(unsigned char *x, unsigned char *y, size_t size) {
    /* sub-optimal, but better than malloc */
    while (size-- > 0) {
        unsigned char c = *x;
        *x++ = *y;
        *y++ = c;
    }
}

// qsort3way(d, 100, sizeof(*d), cmp_double);
void qsort3way(void *base, int n, size_t size,
               int (*cmp)(const void *, const void *))
{
    unsigned char *ptr = (unsigned char *)base;

    while (n > 1) {
        /* use first element as pivot, pointed to by lt */
        int i = 1, lt = 0, gt = n;
        while (i < gt) {
            int c = cmp(ptr + lt * size, ptr + i * size);
            if (c > 0) {
                /* move smaller element before the pivot range */
                swap(ptr + lt * size, ptr + i * size, size);
                lt++;
                i++;
            } else if (c < 0) {
                /* move larger element to the end */
                gt--;
                swap(ptr + i * size, ptr + gt * size, size);
                /* test with that element again */
            } else {
                /* leave identical element alone */
                i++;
            }
        }
        /* array has 3 parts:
         * from 0 to lt excluded: elements smaller than pivot
         * from lt to gt excluded: elements identical to pivot
         * from gt to n excluded: elements greater than pivot
         */
        /* recurse on smaller part, loop on larger to minimize
           stack use for pathological distributions */
        if (lt < n - gt) {
            qsort3way(ptr, lt, size, cmp);
            ptr += gt * size;
            n -= gt;
        } else {
            qsort3way(ptr + gt * size, n - gt, size, cmp);
            n = lt;
        }
    }
}    

static int cmp_double(const void *i, const void *j) {
    /* this comparison function does not handle NaNs */
    if (*(const double *)i < *(const double *)j)
        return -1;
    if (*(const double *)i > *(const double *)j)
        return +1;
    else
        return 0;
}
