#include <stdio.h>

int power(int m, int n);

int power(int m, int n) {

    int i = n;
    int r;
    int k;

    k = 1;
    r = m;
    while (i != 0) {

        if (i % 2 == 0) {
            i = i / 2;
            r *= r;
            printf("i = %d, r = %d, k = %d\r\n", i, r, k);
        } else {
            i = (i - 1) / 2;
            k *= r;
            r *=  r; 
            printf("i = %d, r = %d, k = %d\r\n", i, r, k);
        }
    }

    return k;
}

int main(int argc, char *argv[]) {

    printf("result = %d\r\n", power(2, 9));
    printf("result = %d\r\n", power(2, 11));
    printf("result = %d\r\n", power(2, 12));
    printf("result = %d\r\n", power(3, 4));
    printf("result = %d\r\n", power(3, 9));
    return 0;
}
