#include <stdio.h>

int c;

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[low];

    if (low < high - 1) {
        do {
            do {
                i++;
            } while (arr[i] <= pivot);

            do {
                j--;
            } while (arr[j] > pivot);

            if (i < j)
                swap(&arr[i], &arr[j]);

        } while (i < j);

        swap(&arr[low], &arr[j]);

        return j;
    }
    else return i;
}

void quick_sort(int *arr, int low, int high)
{
   int i;

   if (low < high) 
   {
        i = partition(arr, low, high);
        quick_sort(arr, low, i);
        quick_sort(arr, i + 1, high);
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
    int arr[10] = {8, 5, 7, 11, 3, 2, 9, 10, 15, 1};

    quick_sort(arr, 0, 10);
    
    display(arr, 10);

    return 0;
}

