#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(int *arr, int size)
{
    int i, j, k;

    for (i = 0; i < size - 1; i++) {
        k = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[i])
                k = j;
        }
        swap(&arr[i], &arr[k]);
    }
}

void display(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main(int argc, char *argv[])
{
    int arr[7] = {8, 5, 7, 3, 2, 9, 11};

    selection_sort(arr, 7);

    display(arr, 7);

    return 0;
}
