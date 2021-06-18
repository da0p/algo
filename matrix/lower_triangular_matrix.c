#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_t {
    int *A;
    int n;
} matrix_t;

void set(matrix_t *m, int i, int j, int x) {

    if (i >= j)
        m->A[i * (i + 1) / 2 + j] = x;
}

int get(matrix_t m, int i, int j) {
    if (i >= j)
        return m.A[i * (i + 1) / 2 + j];
    else
        return 0;
}

void display(matrix_t m) {
    int i, j, size;

    for (i = 0; i < m.n; i++) {
        for (j = 0; j < m.n; j++) {
            if (i >= j)
                printf("%d ", m.A[i * (i + 1) / 2 + j]);
            else
                printf("0 ");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {

    matrix_t m;
    int size, val;
    
    printf("Enter size of diagonal matrix: \r\n");
    scanf("%d", &m.n);

    size = m.n * (m.n + 1) / 2;
    m.A = (int *)calloc(size, sizeof(int));

    printf("Enter elements: \r\n");
    for (int i = 0; i < m.n; i++) { 
        for (int j = 0; j < m.n; j++) {
            scanf("%d", &val);
            set(&m, i, j, val);
        }
    }
    printf("%d \n", get(m, 2, 2));
    display(m);

    return 0;
}
