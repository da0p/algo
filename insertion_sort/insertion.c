#include <stdio.h>
#include <stdint.h>

void insertion_sort(int *arr, int size)
{
    int i, j, tmp;
    if (size > 1) {
        for (i = 1; i < size; i++) {
            j = i - 1;
            tmp = arr[i];
            while (j >= 0 && arr[j] > tmp) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = tmp;
        }
    }
}

void display(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int arr[10] = {5, 6, 3, 2, 8, 10, 12, 0, 11, 15};

    insertion_sort(arr, 10);

    display(arr, 10);

    return 0;
}
