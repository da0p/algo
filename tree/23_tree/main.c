#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "twothree_tree.h"


int main(int argc, char *argv[])
{
    TTNode *root = NULL;
    time_t t;

    root = insert(root, root, 10);

    for (int i = 20; i < 500; i+= 10)
        insert(root, root, i);

    printf("in-order display:\n");

    in_order(root, 0);
    
    for (int i = 10; i < 500; i+= 10)
    {
        delete(&root, root, i);
        printf("in-order display:\n");
        in_order(root, 0);
    }

    root = insert(root, root, 10);

    for (int i = 20; i < 200; i+= 10)
        insert(root, root, i);

    in_order(root, 0);

    srand((unsigned) time(&t));

    int k = 0;
    for (int i = 0; i < 50; i++) {
        k = rand() % 50;
        printf("delete %d\n", k * 10);
        delete(&root, root, k * 10);
        printf("in-order display:\n");
        in_order(root, 0);
    }

    destroy_tt_tree(root);

    root = NULL;

    return 0;
}
