#include <stdio.h>
#include <string.h>


void dfs(int u, int *A, int rows, int cols, int *visited)
{
    if (visited[u] == 0)
        printf("%d ", u);
    
    visited[u] = 1;

    for (int v = 0; v < cols; v++) {
        if ((*(A + (u * cols) + v) == 1) && visited[v] == 0) {
            dfs(v, A, rows, cols, visited);
        }
    }
}

int main (int argc, char *argv[])
{
    int A[7][7] = {{0, 1, 1, 1, 0, 0, 0},
                   {1, 0, 1, 0, 0, 0, 0},
                   {1, 1, 0, 1, 1, 0, 1},
                   {1, 0, 1, 0, 1, 0, 1},
                   {0, 0, 1, 1, 0, 1, 1},
                   {0, 0, 1, 0, 1, 0, 0},
                   {0, 0, 0, 0, 1, 0, 0}};

    int visited[7] = {0};

    dfs(0, &A[0][0], 7, 7, visited);

    printf("\n");

    memset(visited, 0, 7 * sizeof(int));

    dfs(1, &A[0][0], 7, 7, visited);

    printf("\n");

    memset(visited, 0, 7 * sizeof(int));

    dfs(2, &A[0][0], 7, 7, visited);

    printf("\n");

    memset(visited, 0, 7 * sizeof(int));

    dfs(3, &A[0][0], 7, 7, visited);

    printf("\n");

    memset(visited, 0, 7 * sizeof(int));

    dfs(4, &A[0][0], 7, 7, visited);

    printf("\n");

    memset(visited, 0, 7 * sizeof(int));

    dfs(5, &A[0][0], 7, 7, visited);

    printf("\n");

    memset(visited, 0, 7 * sizeof(int));

    dfs(6, &A[0][0], 7, 7, visited);

    printf("\n");

    return 0;
}
