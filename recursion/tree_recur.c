#include <stdio.h>

void fun(int n) {
    if (n > 0) {
        printf("%d\r\n", n);
        fun(n - 1);
        fun(n - 1);
    }
}

int main(int argc, char *argv[]) {
    fun(3);
    return 0;
}
