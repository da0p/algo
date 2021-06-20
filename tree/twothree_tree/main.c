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

    insert(root, root, 90);
    
    insert(root, root, 100);

    insert(root, root, 130);

    insert(root, root, 150);

    insert(root, root, 170);

    //insert(root, root, 190);

    printf("pre-order display:\n");

    pre_order(root);

    printf("\n");

    printf("level-order display:\n");

    level_order(root);

    printf("\n");

    printf("post-order display:\n");

    post_order(root);

    printf("\n");

    printf("in-order display:\n");

    in_order(root, 0);

    printf("\n");

    printf("search for 70\n");

    TTNode *node = NULL;
    node = search(root, 70);
    if (node != NULL) { 
        if (node->stat == 2)
            printf("Found [%d, %d]\n", node->first, node->second);
        else if (node->stat == 1)
            printf("Found [%d, -]\n", node->first);
    }

    return 0;
}
