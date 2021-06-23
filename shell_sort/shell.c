#include <stdio.h>

void shell_sort(int *A, int n)
{
    int gap, i, j, temp;

    for (gap = n / 2; gap >= 1; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = A[i];
            j = i - gap;
            while (j >= 0 && A[j] > temp) {
                A[j + gap] = A[j];
                j = j - gap;
            }
            A[j + gap] = temp;
        }
    }
}


void display(int *A, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}


int main(int argc, char *argv[]) 
{
    int A[10] = {16, 24, 9, 0, 2, 8, 45, 99, 87, 10};

    shell_sort(A, 10);

    display(A, 10);

    return 0;
}
