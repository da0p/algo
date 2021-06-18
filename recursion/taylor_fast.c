#include <stdio.h>

double e(int x, int n);

double e(int x, int n) {
    static double s = 1;

    if (n == 0)
        return s;

    s = 1 + x * s / n;

    return e(x, n - 1);
}

int main(int argc, char *argv[]) {
    printf("result = %lf\r\n", e(2, 10));
    return 0;
}
