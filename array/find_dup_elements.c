#include <stdio.h>
#include <stdlib.h>

int count_dups_sorted(int *array, int size) 
{
    int i, j, count;

    count = 0;
    for (i = 0; i < size - 1; i++) {
       if (array[i] == array[i + 1]) {
          count++; 
       }
    }

    return count;
}

int count_dups_unsorted(int *array, int size) 
{
    int i, j, count;

    count = 0;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (array[i] == array[j] && array[j] != -1) {
                count++;
                array[i] = -1;
            }
        }
    }
    
    return count;
}

int count_dups_hash(int *array, int size)
{
    int i, max, min, count;
    int *tmp;

    max = array[0];
    min = array[0];
    for (i = 1; i < size; i++) {
        if (max < array[i])
            max = array[i];
        if (min > array[i])
            min = array[i];
    }

    tmp = (int *) calloc(max + 1, sizeof(int));
    for (i = 0; i < max + 1; i++) {
        tmp[array[i]]++;
    }

    for (i = 0; i < max + 1; i++)
        if (tmp[i] > 1)
            count += tmp[i] - 1;

    free(tmp);

    return count;
}

int main(int argc, char *argv[])
{

    int *arr;
    int size;

    printf("Enter size of array: \n");
    scanf("%d", &size);

    printf("Enter elements: \r\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    //printf("Number of duplicates = %d\r\n", count_dups_unsorted(arr, size));
    
    printf("Number of duplicates = %d\r\n", count_dups_hash(arr, size));

    return 0;
}
