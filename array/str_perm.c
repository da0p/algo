#include <stdio.h>
#include <string.h>

void swap_chr(char *a, char *b) {

    char tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void perm_str(char *str, int *A, char *r, int k) {
    
    int i;

    if (str[k] == '\0')
    {
        r[k] = '\0';
        printf("%s ", r);
    }
    else 
    {
        for (i = 0; str[i] != '\0'; i++) {
            if (A[i] == 0) {
                r[k] = str[i];
                A[i] = 1;
                perm_str(str, A, r, k + 1);
                A[i] = 0;
            }
        }
    }
}

void perm_str_swap(char *str, int low, int high) {

    int i;

    if (low == high)
        printf("%s ", str);
    else {
        for (i = low; i <= high; i++){
            swap_chr(&str[i], &str[low]);
            perm_str_swap(str, low + 1, high);
            swap_chr(&str[i], &str[low]);
        }
    }
}

int main(int argc, char *argv[]) {

    char arr[] = "ABC";
    int A[10] = {0};
    char r[10];

    printf("First method:\r\n");
    perm_str(arr, A, r, 0);

    printf("\r\n");
    printf("Second method:\r\n");
    perm_str_swap(arr, 0, 2);
    printf("\r\n");

    return 0;
}
