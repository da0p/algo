#include <stdio.h>
#include <stdlib.h>

int rfib (int n, int *mem);

int num_calls = 0;

int rfib(int n, int *mem) {
   
    num_calls += 1;
    if (n < 2) {
       mem[n] = n;
       return n;
    } 
    else {
        if (mem[n - 1] == -1) mem[n - 1] = rfib(n - 1, mem);
        if (mem[n - 2] == -1) mem[n - 2] = rfib(n - 2, mem);

        return mem[n - 1] + mem[n - 2];
    }
}

int main (int argc, char *argv[]) {

    int *mem;
    int n;
    int r;

    printf("Enter an integer: \r\n");
    scanf("%d", &n);
    printf("You enter %d \r\n", n);

    mem = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        mem[i] = -1;

    r = rfib(n, mem);
    printf("r = %d\r\n", r);

    printf("num_calls = %d\r\n", num_calls);

    free(mem);
    mem = NULL;

    return 0; 
}
