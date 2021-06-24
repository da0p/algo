#include <stdio.h>
#include <stdlib.h>

void bfs(int *A, int size)
{
    int v = 0;
    
    int i = 0;

    int *visited = NULL;

    while (A[v++] < size);

    printf("v = %d\n", v);

    visited = (int *) calloc(v, sizeof(int));

    if (visited == NULL) return;

    visited[i] = 1;

    printf("%d ", i);

    while (A[i + 1] < size) {
    
        for (int j = A[i]; j < A[i + 1]; j++) {
            if (!visited[A[j]]) {
                printf("%d ", A[j]);
                visited[A[j]] = 1;
            }
        }
        i++;
    }

    printf("\n");
}


int main (int argc, char *argv[])
{

    /* vertex = 7, edges = 8 -> size = 7 + 8 * 2 + 1 = 24 */
    int A[24] = {8, 11, 13, 15, 19, 22, 23, 25, 1, 2, 3, 0, 3, 0, 3, 0, 1, 2, 4, 3, 5, 6, 4, 4};

    bfs(A, 24);

    return 0;
}
