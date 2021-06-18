#include <stdio.h>

int nCr(int n, int r);

int nCr(int n, int r) {

    if (r == 0 || r == n)
        return 1;
    else 
        return nCr(n - 1, r - 1) + nCr(n - 1, r);
}

int main (int argc, char *argv[]) {

    int n, r;

    printf("Test nCr: \r\n");

    while (1) {
        printf("Enter n and r: \n");

        if(scanf("%d %d", &n, &r) == 2) {
            printf("You enter n = %d, r = %d\r\n", n, r);
        } else {
            printf("Error. Please supply 4 integers");
        }

        if (n < 0 || r < 0 || r > n)
            printf("Invalid n, r\r\n");
        else
            break;
    }

    printf("nCr(%d, %d) = %d\r\n", n, r, nCr(n, r));

    return 0;
}
