#include <stdio.h> 
#include <stdlib.h>

int find_missing_element(int *array, int size) {

    int i;
    int tmp;

    tmp = array[0]; 
    for (i = 0; i < size; i++) {
        if (array[i] - i != tmp) {
            return i + tmp;
        }
    }

    return -1;
}

void find_missing_elements(int *array, int size, int **res, int *ssize) {
    int i, j;
    int _dff, dff;

    *res = (int *) malloc(size * sizeof(int));
    dff = array[0];
    j = 0;
    for (i = 0; i < size; i++) {
        _dff = array[i] - i;
        if (_dff != dff) {
            while (dff < _dff) {
                *(*res + j) = i + dff; 
                j++;
                dff++;
            }
        }
    }

    *res = (int *) realloc(*res, j * sizeof(int));
    *ssize = j;
}

void find_missing_elements_hash(int *array, int size, int **res, int *ssize) {

    int i, j;
    int max, min;
    int *tmp;

    max = array[0];
    min = array[0];
    for (i = 1; i < size; i++) {
       if (max < array[i]) 
           max = array[i];
       if (min > array[i])
           min = array[i];
    }
    
    tmp = (int *) calloc(max - min + 1, sizeof(int));
    
    for (i = 0; i < size; i++) {
        tmp[array[i] - min] = 1;
    }

    j = 0;
    *res = (int *) malloc(size * sizeof(int));
    for (i = 0; i < max - min + 1; i++) {
        if (!tmp[i]) {
            *(*res + j) = i + min;
            j++;
        }
    } 
    *res = (int *) realloc(*res, j * sizeof(int));
    *ssize = j;
}

void display(int *array, int size) {

    for (int i = 0; i < size; i++) 
        printf("%d ", array[i]);
    printf("\r\n");
}

int main(int argc, char *argv[]) {

    int *arr;
    int *res;
    int size, ssize;

    printf("Enter size of array: \r\n");
    scanf("%d", &size);
    arr = (int *) malloc(size * sizeof(int));
   
    printf("Enter all elements: \r\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    //printf("missing element = %d\r\n", find_missing_element(arr, size));

    //find_missing_elements(arr, size, &res, &ssize);

    find_missing_elements_hash(arr, size, &res, &ssize);
    display(res, ssize);

    free(res);
    free(arr);
    res = NULL;
    arr = NULL;

    return 0;
}
