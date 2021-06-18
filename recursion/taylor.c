#include <stdio.h>

double e(int x, int n);

double e(int x, int n) {
    static double p = 1;
    static double f = 1;
    double r;

    if (n == 0)
        return 1;

    r = e(x, n - 1);
    p = p * x;
    f = f * n;

    return r + p / f;
}

int main() {
    printf("%lf \r\n", e(4, 15));

    return 0;
}
