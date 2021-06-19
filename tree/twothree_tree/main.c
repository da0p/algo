#include <stdio.h>
#include "twothree_tree.h"


int main(int argc, char *argv[])
{
    TTNode *root = NULL;

    root = insert(root, root, 20);

    insert(root, root, 30);

    insert(root, root, 40);

    insert(root, root, 50);

    insert(root, root, 60);

    insert(root, root, 10);

    insert(root, root, 15);

    insert(root, root, 70);

    insert(root, root, 80);

    pre_order(root);

    printf("\n");

    level_order(root);

    printf("\n");

    in_order(root, 0);

    printf("\n");

    return 0;
}
