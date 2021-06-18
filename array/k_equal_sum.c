#include <stdio.h>
#include <stdlib.h>

int count_equal_sum(int *array, int size, int sum) 
{
    int max, min, i, count;
    int *tmp;

    max = array[0];
    min = array[0];
    for (i = 1; i < size; i++) {
        if (max < array[i])
            max = array[i];
        if (min > array[i])
            min = array[i];
    }

    tmp = (int*) calloc(max + 1, sizeof(int));

    count = 0;
    for (i = 0; i < max + 1; i++) {
        if (array[i] <= sum) {
            if (tmp[sum - array[i]] != 0)
                count++;
        }
        tmp[array[i]] = 1;
    }

    free(tmp);

    return count;
}

int main(int argc, char *argv[]) {

    int *arr, size, i, sum;

    printf("Enter array's size: \r\n");
    scanf("%d", &size);

    arr = (int *) malloc(size * sizeof(int));
    printf("Enter all elements:\r\n");
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("Enter sum: \r\n");
    scanf("%d", &sum);

    printf("Number of pairs = %d\r\n", count_equal_sum(arr, size, sum));

    return 0;
}
