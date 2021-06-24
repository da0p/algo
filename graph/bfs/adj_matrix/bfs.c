#include <stdio.h>
#include <stdlib.h>
#include "queue_ll.h"

void bfs(int n_start, int *A, int rows, int cols)
{
    int u, flag;

    int *visited = NULL;

    visited = (int *) calloc(rows, sizeof(int));

    if (visited == NULL) return;

    Queue *q = create_queue(rows);
    
    visited[n_start] = 1;

    printf("%d ", n_start);

    enqueue(q, n_start);

    while (!is_empty(q)) {
        u = dequeue(q, &flag);

        if (flag) {
            for (int j = 0; j < cols; j++) {
                if (*(A + (u * cols) + j) == 1 && visited[j] == 0) {
                    printf("%d ", j);
                    enqueue(q, j);
                    visited[j] = 1;
                }
            }
        }
    }

    destroy(q);

    free(visited);
}


int main (int argc, char *argv[])
{
    int A[7][7] = {{0, 1, 1, 1, 0, 0 ,0},
                   {1, 0, 1, 0, 0, 0, 0},
                   {1, 1, 0, 1, 1, 0, 1},
                   {1, 0, 1, 0, 1, 0, 1},
                   {0, 0, 1, 1, 0, 1, 1},
                   {0, 0, 1, 0, 1, 0, 0},
                   {0, 0, 0, 0, 1, 0, 0}};

    bfs(0, &A[0][0], 7, 7);

    printf("\n");

    return 0;
}
