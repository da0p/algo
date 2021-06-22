#include <stdio.h>
#include <stdint.h>

void swap(int *a, int *b) 
{
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *arr, int size) 
{
    int flag;
    for (int i = 0; i < size - 1; i++) {
        flag = 0;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0) break;
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
    int arr[10] = {8, 5, 6, 3, 2, 10, 12, 15, 0, 11};

    bubble_sort(arr, 10);

    display(arr, 10);

    return 0;
}
