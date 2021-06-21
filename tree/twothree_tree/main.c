#include <stdio.h>
#include "twothree_tree.h"


int main(int argc, char *argv[])
{
    TTNode *root = NULL;

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
    TTNode *node = NULL;
    node = search(root, 90);
    if (node != NULL) { 
        if (node->stat == 2)
            printf("Found [%d, %d]\n", node->first, node->second);
        else if (node->stat == 1)
            printf("Found [%d, -]\n", node->first);
    }


    return 0;
}
