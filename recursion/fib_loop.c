#include <stdio.h>

int fib(int n) {
    int t0 = 0, t1 = 1;
    int s, i;

    if (n <= 1) return n;

    for (i = 2; i <= n; i++) {
        s = t0 + t1;
        t0 = t1;
        t1 = s;
    }

    return s;
}

int main(int argc, char *argv[]) {

    printf("r = %d\r\n", fib(10));
}
