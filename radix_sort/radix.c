#include <stdio.h>
#include <stdlib.h>

void display(int *A, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

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

int find_num_digits(int num)
{
    int i = num;
    int k = 0;

    do {
        k++;
        i = i / 10;
    } while (i != 0);

    return k;
}

int find_digit(int num, int ind)
{
    int d;

    d = num;
    for (int i = 0; i < ind; i++)
        d = d / 10;

    d = d % 10;

    return d;
}

void radix_sort(int *A, int size)
{
    int max, passes, k, n;
    int bucket[size][10];
    int e[10] = {0};

    max = find_max(A, size);

    passes = find_num_digits(max);

    for (int i = 0; i < passes; i++) {
       for (int j = 0; j < size; j++) {
         k = find_digit(A[j], i);  
         bucket[e[k]][k] = A[j];
         e[k]++;
       }

       n = 0;
       for (int j = 0; j < 10; j++) {
           for (int c = 0; c < e[j]; c++) {
               A[n++] = bucket[c][j]; 
           }
           e[j] = 0;
       }
    }
}



int main (int argc, char *argv[])
{
    int A[11] = {10, 43, 123, 44, 99, 324, 99, 144, 443, 232, 5643};

    radix_sort(A, 11);

    display(A, 11);

    return 0;
}
