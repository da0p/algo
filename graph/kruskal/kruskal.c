#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void display(int *P, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) { 
           printf("%d\t| ", *(P + i * cols + j)); 
        }
        printf("\n");
    }
}

int find_parent(int *s, int u)
{
    //printf("u = %d\n", u);
    while (s[u] > 0) {
        u = s[u];
    }

    return u;
}

void union_set(int *s, int u, int v)
{
    if (s[u] < s[v]) {
        //printf("s[u] = %d, u = %d, s[v] = %d, v = %d\n", s[u], u, s[v], v);
        s[u] = s[u] + s[v];
        s[v] = u;
    }
    else {
        s[v] = s[u] + s[v];
        s[u] = v;
        //printf("s[u] = %d, u = %d, s[v] = %d, v = %d\n", s[u], u, s[v], v);
    }

}


void kruskal(int *A, int rows, int cols)
{ 
    int s[rows];
    int *visited = NULL;
    int t[2][rows - 1];
    int **E = (int **) malloc(3 * sizeof(int *));
    int i, j, k = 0;
    int edges = 0, min = 0, ecols = 0;
    int u, v, r = 0, m = 0;

    for (i = 0; i < rows; i++)
        s[i] = -1;

    if (E == NULL) {
        printf("Failed to obtain edges from adjacent matrix\n");
        return;
    }

    for (i = 0; i < rows; i++) {
        for (j = i; j < cols; j++) {
            if (*(A + i * cols + j) != INT_MAX)
                ecols++;
        }
    }

    /* allocate contiguou memory */
    E[0] = (int *) malloc(3 * ecols * sizeof(int));
    for (i = 1; i < 3; i++) {
        E[i] = E[0] + i * ecols;
        if (E[i] == NULL) {
            printf("Failed to allocate memory for edges\n");
            return;
        }
    }
    
    for (i = 0; i < rows; i++) {
        for (j = i; j < cols; j++) {
            if (*(A + i * cols + j) < INT_MAX) {
                *(*E + edges) = i;
                *(*E + ecols + edges) = j;
                *(*E + 2 * ecols + edges) = *(A + i * cols + j);
                edges++;
            }
        }
    }

    /* Edge table */
    printf("Display edge tables:\n");
    display(&E[0][0], 3, ecols);

    visited = (int *) calloc(edges, sizeof(int));
    if (visited == NULL) {
        printf("Failed to allocated memory for marking\n");
        return;
    }

    printf("number of edges = %d\n\n", edges);
    printf("Kruskal's algorithm:\n");

    while (k < edges) {

        min = INT_MAX;

        for (i = 0; i < edges; i++) {
            if (visited[i] == 0 && min > *(*E + 2 * ecols + i)) {
                min = *(*E + 2 * ecols + i);
                m = i;
            }
        }
        visited[m] = 1;

        u = find_parent(s, E[0][m]);
        v = find_parent(s, E[1][m]);
        if (u != v) {
            t[0][r] = E[0][m];
            t[1][r] = E[1][m];
            union_set(s, u, v);
            r++;
        }
        k++;
    }

    display(&t[0][0], 2, rows - 1);

    free(visited);
    free(E[0]);
    free(E);
}

int main(int argc, char *argv[])
{
    int A[7][7] = { {INT_MAX, 25     , INT_MAX, INT_MAX, INT_MAX, 5      , INT_MAX},
                    {25     , INT_MAX, 12     , INT_MAX, INT_MAX, INT_MAX, 10},
                    {INT_MAX, 12     , INT_MAX, 8      , INT_MAX, INT_MAX, INT_MAX},
                    {INT_MAX, INT_MAX, 8      , INT_MAX, 16     , INT_MAX, 14},
                    {INT_MAX, INT_MAX, INT_MAX, 16     , INT_MAX, 20     , 18},
                    {5      , INT_MAX, INT_MAX, INT_MAX, 20     , INT_MAX, INT_MAX},
                    {INT_MAX, 10     , INT_MAX, 14     , 18     , INT_MAX, INT_MAX}
                    };

    kruskal(&A[0][0], 7, 7);

    return 0;
}
