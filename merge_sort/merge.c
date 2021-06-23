#include <stdio.h>
#include <stdlib.h>

void display(int *A, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void merge(int *A, int low, int mid, int high)
{
    int i, j, k;
    int C[high];

    i = low;
    j = mid + 1;
    k = 0;
    while (i <= mid && j <= high) {
        if (A[i] < A[j]) 
            C[k++] = A[i++];
        else C[k++] = A[j++];
    }

    for(;j <= high; j++) C[k++] = A[j];
    for(;i <= mid; i++) C[k++] = A[i];

    k = 0;
    for (i = low; i <= high; i++) A[i] = C[k++];
}

void merge_sort(int *A, int low, int high) 
{
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(A, low, mid);
        merge_sort(A, mid + 1, high);
        merge(A, low, mid, high);
    }
}

void merge_sort_it(int *A, int size) 
{
    int i = 0, j = 0;
    int l, h, m;

    for (i = 2; i <= size; i = 2 * i) {
       for (j = 0; j + i - 1 < size; j += i) {
           l = j;
           h = j + i - 1;
           m = (l + h) / 2;
           merge(A, l, m, h);
       }
    }

    if (i / 2 < size) {
        merge(A, l, h, size - 1);
    }
}

int main(int argc, char *argv[])
{
    int arr1[10] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    int arr2[10] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};

    int l = 0, h = 9;
    int m = (l + h) / 2;

    merge_sort(arr1, l, h);

    display(arr1, 10);

    merge_sort_it(arr2, 10);

    display(arr2, 10);

    return 0;
}
