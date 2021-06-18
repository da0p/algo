#include <stdio.h>
#include <stdlib.h>

struct Array 
{
    int *A;
    int size;
    int length;
};

void display(struct Array arr)
{
    int i;
    printf("\r\nElements are\n");
    for (i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

void append(struct Array *arr, int x)
{
    if (arr->length < arr->size)
        arr->A[arr->length++] = x;
}

void insert(struct Array *arr, int index, int x)
{
    int i;
    if (index >= 0 && index <= arr->length && arr->length < arr->size) {
        for (i = arr->length; i > index; i--)
            arr->A[i] = arr->A[i - 1];
        arr->A[index] = x;
        arr->length++;
    }

}

int delete(struct Array *arr, int index)
{
    int x = 0;
    int i;

    if (index >= 0 && index < arr->length)
    {
        x = arr->A[index];
        for (i = index; i < arr->length - 1; i++)
            arr->A[i] = arr->A[i + 1];
        arr->length--;
    }

    return x;
}

int linear_search(struct Array arr, int key)
{
    int i;
    
    for (i = 0; i < arr.length; i++) {
        if (key == arr.A[i])
            return i;
    }

    return -1;
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int transpo_linear_search(struct Array *arr, int key)
{
    int i;
    
    for (i = 0; i < arr->length; i++)
    {
        if (key == arr->A[i])
        {
            swap(&arr->A[i], &arr->A[i - 1]);

            return i;
        }
    }

    return -1;
}

int head_mov_linear_search(struct Array *arr, int key)
{
    int i;

    for (i = 0; i < arr->length; i++)
    {
        if (key == arr->A[i])
        {
            swap(&arr->A[i], &arr->A[0]);

            return i;
        }
    }

    return -1;
}

int binary_search(struct Array arr, int key)
{
    int low, mid, high;
    
    low = 0;
    high = arr.length - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (key == arr.A[mid])
            return mid;
        else if (key < arr.A[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

int rbinary_search(struct Array arr, int low, int high, int key)
{
    int mid;

    if (low <= high) {


        mid = (low + high) / 2;

        if (key == arr.A[mid])
            return mid;
        else if (key < arr.A[mid])
            return rbinary_search(arr, low, mid - 1, key);
        else
            return rbinary_search(arr, mid + 1, high, key);
    }

    return -1;

}

int get(struct Array arr, int index)
{
    if (index >= 0 && index < arr.length)
        return arr.A[index];
    return -1;
}

void set(struct Array *arr, int index, int value)
{
    if (index >= 0 && index < arr->length)
        arr->A[index] = value;
}

int find_max(struct Array arr)
{
    int i;
    int max = arr.A[0];

    for (i = 1; i < arr.length; i++)
    {
        if (arr.A[i] > max)
            max = arr.A[i];
    }

    return max;
}

int find_min(struct Array arr)
{
    int i;
    int min = arr.A[0];

    for (i = 1; i < arr.length; i++)
    {
        if (arr.A[i] < min)
            min = arr.A[i];
    }

    return min;
}

int sum(struct Array arr)
{
    int s = 0;
    int i;

    for (i = 0; i < arr.length; i++)
        s += arr.A[i];

    return s;
}

float avg(struct Array arr)
{
    return (float)sum(arr) / arr.length;
}

void reverse(struct Array *arr)
{

    int *temp;
    int i, j;

    temp = (int *)malloc(arr->length * sizeof(int));

    for (i = arr->length - 1, j = 0; i >= 0, j < arr->length; i--, j++) {
        temp[j] = arr->A[i];
    }

    for (i = 0; i < arr->length; i++) {
        arr->A[i] = temp[i];
    }

    free(temp);
}

void reverse_in(struct Array *arr) {
    int i, j;

    for (i = 0, j = arr->length -1; i < j; i++, j--) {
        swap(&arr->A[i], &arr->A[j]);
    }
}

void shift_left(struct Array *arr) {

    int i;

    for (i = 0; i < arr->length - 1; i++) {
        arr->A[i] = arr->A[i + 1];
    }
    arr->A[arr->length - 1] = 0;
    arr->length--;
}

void shift_right(struct Array *arr) {
    int i;

    if (arr->length + 1 <= arr->size) {

        arr->length++;
        for (i = arr->length - 1; i > 0; i--) {
            arr->A[i] = arr->A[i - 1];
        }

        arr->A[0] = 0;
    }
}

void rotate_left(struct Array *arr) {

    int i, tmp;

    tmp = arr->A[0];
    for (i = 0; i < arr->length - 1; i++) {
        arr->A[i] = arr->A[i + 1];
    }
    arr->A[arr->length - 1] = tmp;
}

void rotate_right(struct Array *arr) {
    
    int i, tmp;

    tmp = arr->A[arr->length - 1];
    for (i = arr->length -1; i > 0; i--) {
        arr->A[i] = arr->A[i - 1];
    }
    arr->A[0] = tmp;
}

void insert_sort(struct Array *arr, int x)
{
    int i = arr->length - 1;

    if (arr->length == arr->size) {
        return;
    }

    while (i >= 0 && arr->A[i] > x) {
        arr->A[i + 1] = arr->A[i];
        i--;
    }
    arr->A[i + 1] = x; 
    arr->length++;
}

int is_sorted(struct Array arr)
{
    int i;
    
    for (i = 0; i < arr.length - 1; i++) {
        if (arr.A[i] > arr.A[i + 1])
            return 0;
    }

    return 1;
}

void rearrange(struct Array *arr)
{
    int i, j;

    i = 0;
    j = arr->length - 1;

    while (i < j) {
        while (arr->A[i] < 0) i++;
        while (arr->A[j] >= 0) j--;

        if (i < j)
            swap(&arr->A[i], &arr->A[j]);
    }
}

struct Array* merge(struct Array *src1, struct Array *src2)
{
    int i, j, k;
    struct Array *dest;
    
    dest = (struct Array *) malloc(sizeof(struct Array));
    dest->A = (int *) malloc((src1->length + src2->length) * sizeof(int));
    dest->length = src1->length + src2->length;
    dest->size = src1->length + src2->length;

    i = 0;
    j = 0;
    k = 0;
    while (i < src1->length && j < src2->length) {
        if (src1->A[i] < src2->A[j]) {
            dest->A[k] = src1->A[i];
            i++;
            k++;
        }
        else {
            dest->A[k] = src2->A[j];
            k++;
            j++;
        }
    }

    for (; i < src1->length; i++)
        dest->A[k++] = src1->A[i];

    for (; j < src2->length; j++)
        dest->A[k++] = src2->A[j];

    return dest;
}

struct Array* union_array(struct Array *src1, struct Array *src2)
{
    int i, j, k;
    struct Array *dest;

    dest = (struct Array *) malloc(sizeof(struct Array));
    dest->A = (int *) malloc((src1->length + src2->length) * sizeof(int));
    dest->length = src1->length + src2->length;
    dest->size = src1->length + src2->length;

    i = 0;
    j = 0;
    k = 0;
    while (i < src1-> length && j < src2->length) {
        if (src1->A[i] < src2->A[j]) {
            dest->A[k++] = src1->A[i++];
        }
        else if (src1->A[i] > src2->A[j]) {
            dest->A[k++] = src2->A[j++];
        }
        else {
            dest->A[k++] = src1->A[i++];
            j++;
        }
    }

    for (;i < src1->length; i++)
        dest->A[k++] = src1->A[i];
   
    for (;j < src2->length; j++)
        dest->A[k++] = src2->A[j];

    dest->length = k;

    return dest;
}

struct Array* intersection(struct Array *src1, struct Array *src2)
{
    int i, j, k;
    struct Array *dest;
    int _size;

    dest = (struct Array*) malloc(sizeof(struct Array));
    if (src1->length < src2->length)
        _size = src1->length;
    else
        _size = src2->length;
    
    dest->A = (int*) malloc( _size * sizeof(int));
    dest->length = _size;
    dest->size = _size;

    i = 0;
    j = 0;
    k = 0;
    while (i < src1->length && j < src2->length) {
       if (src1->A[i] < src2->A[j])
           i++;
       else if (src1->A[i] > src2->A[j])
           j++;
       else {
           dest->A[k++] = src1->A[i++];
           j++;
       }
    }

    dest->length = k;
    return dest;
}

int main()
{

    struct Array arr1;
    int ch = 0;
    int val, index;

    printf("Enter size of an Array\r\n");
    scanf("%d", &arr1.size);
    arr1.A = (int *) malloc(arr1.size * sizeof(int));
    arr1.length = 0;
    
    while (ch < 6) {
        printf("Menu\r\n");
        printf("1. Insert\r\n");
        printf("2. Delete\r\n");
        printf("3. Search\r\n");
        printf("4. Sum\r\n");
        printf("5. Display\r\n");
        printf("6. Exit\r\n");

        printf("Enter your choice\r\n");
        scanf("%d", &ch);

        switch(ch)
        {
        case 1: 
            printf("Enter an element and index ");
            scanf("%d %d", &val, &index);
            insert(&arr1, index, val);
            break;

        case 2:
            printf("Enter index ");
            scanf("%d", &index);
            delete(&arr1, index);
            break;

        case 3:
            printf("Enter a value ");
            scanf("%d", &val);
            linear_search(arr1, val) == -1 ? printf("%d is not found", val) : printf("%d is found", val);
            break;

        case 4: 
            printf("Sum = %d\r\n", sum(arr1));
            break;

        case 5: 
            display(arr1);
            break;

        case 6:
            break;

        }
    }

    return 0;
}
