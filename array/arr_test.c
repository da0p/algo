#include <stdio.h>

int main(int argc, char *argv[]) {
    unsigned int x[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    printf("%ls, %ls, %ls", x+3, *(x + 3), *(x + 2) + 3);

    return 0;
}
