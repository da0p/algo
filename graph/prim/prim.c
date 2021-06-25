#include <stdio.h>
#include <string.h>
#include <limits.h>

void display(int *P, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) { 
           printf("%d | ", *(P + i * cols + j)); 
        }
        printf("\n");
    }
}

void find_min_cost_edge(int *A, int rows, int cols, int *ii, int *jj)
{
    int min = *A; // A[0][0]
    
    *ii = 0;
    *jj = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols; j++) {
            if (*(A + i * cols + j) < min) {
                min = *(A + i * cols + j);
                *ii = i;
                *jj = j;
            }
        }
    }
}

void prim(int *A, int rows, int cols)
{

    int near[rows];
    int t[2][rows - 1];
    int k, min, ii = 0, jj = 0;
    int i, j;

    find_min_cost_edge(A, rows, cols, &t[0][0], &t[1][0]);

    memset(near, 0, rows * sizeof(int));

    near[t[0][0]] = -1;
    near[t[1][0]] = -1;

    for (k = 1; k < rows - 1; k++) {
        min = INT_MAX;
        for (i = 0; i < rows; i++) {
            if (near[i] != -1) {
                if ((*(A + i * cols + t[0][k - 1])) < (*(A + i * cols + t[1][k - 1]))) {
                    near[i] = t[0][k - 1];
                }
                else {
                    near[i] = t[1][k - 1];
                }
            }
        }

        for (j = 0; j < rows; j++) {
            if (near[j] != -1) {
                if (min > *(A + j * cols + near[j])) {
                    min = *(A + j * cols + near[j]); 
                    ii = j;
                    jj = near[j];
                }
            }
        }

        t[0][k] = ii;
        t[1][k] = jj;
        near[ii] = -1;
    }

    display(&near[0], 1, rows);
    display(&t[0][0], 2, rows - 1);
}

int main (int argc, char *argv[])
{

    int A[7][7] = { {INT_MAX, 25     , INT_MAX, INT_MAX, INT_MAX, 5      , INT_MAX},
                    {25     , INT_MAX, 12     , INT_MAX, INT_MAX, INT_MAX, 10},
                    {INT_MAX, 12     , INT_MAX, 8      , INT_MAX, INT_MAX, INT_MAX},
                    {INT_MAX, INT_MAX, 8      , INT_MAX, 16     , INT_MAX, 14},
                    {INT_MAX, INT_MAX, INT_MAX, 16     , INT_MAX, 20     , 18},
                    {5      , INT_MAX, INT_MAX, INT_MAX, 20     , INT_MAX, INT_MAX},
                    {INT_MAX, 10     , INT_MAX, 14     , 18     , INT_MAX, INT_MAX}
                    };

    prim(&A[0][0], 7, 7);

    return 0;
}
