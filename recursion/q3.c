#include <stdio.h>

int f(int *x, int c);

int f(int *x, int c) {

    static int rr;
    c = c - 1;

    if (c == 0) return 1;
    *x = *x + 1;
    printf("*x = %d, c = %d\r\n", *x, c);
    rr =  f(x, c) * (*x);
    printf("rr = %d\r\n", rr);

    return rr;
}

int main(int argc, char *argv[]) {

    int p = 5;
    printf("r = %d\r\n", f(&p, p));

    printf("p = %d\r\n", p);

    return 0;
}
