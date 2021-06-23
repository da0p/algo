#include <stdio.h>
#include <stdlib.h>

int find_max(int *A, int size) 
{
    int max;

    max = A[0];
    for (int i = 1; i < size; i++) {
        if (A[i] > max)
            max = A[i];
    }
    return max;
}

void count_sort(int *A, int size) 
{
    int max, k;
    int *C;

    max = find_max(A, size);

    C = (int *) calloc( max + 1, sizeof(int));

    if (C != NULL) {
        for (int i = 0; i < size; i++)
            C[A[i]]++;

        k = 0;
        for (int i = 0; i < max + 1; i++) {
           if (C[i] != 0) {
               for (int j = 0; j < C[i]; j++)
                   A[k++] = i;
           }
        }
    }
}

void display(int *A, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(int argc, char *argv)
{
    int A[10] = {4, 1, 9, 0, 45, 29, 11, 24, 29, 10};

    count_sort(A, 10);

    display(A, 10);

    return 0;
}
