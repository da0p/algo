#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, char *argv[])
{
    int pre[] = {30, 20, 10, 15, 25, 40, 50, 45};

    int pre2[] = {30, 40, 50, 45};
    
    Tree *t = NULL;

    t = new_tree();

    t = create_bst();

    printf("Pre-order display\n");
    if (t != NULL)
        pre_order(t->root);
    printf("\n");

    destroy_tree(t->root);

    free(t);
    
    t = NULL;

    t = new_tree();

    if (t != NULL) {
        printf("Insert new nodes\n");

        t->root = rinsert(t->root, 50);

        rinsert(t->root, 30);

        rinsert(t->root, 80);

        rinsert(t->root, 20);

        rinsert(t->root, 40);

        rinsert(t->root, 60);

        rinsert(t->root, 90);

        delete(&t->root, t->root, 20);

        printf("Pre-order display\n");

        pre_order(t->root);

        printf("\n");


        if (rsearch(t->root, 20) != NULL)
            printf("Found element\n");

        if (rsearch(t->root, 100) != NULL)
            printf("Found element\n");
        else
            printf("Not found element\n");

        destroy_tree(t->root);

        free(t);

        t = NULL;
    }

    t = new_tree();

    t = create_from_pre_order(pre, 8);
    
    if (t != NULL)
        pre_order(t->root);
    printf("\n");

    destroy_tree(t->root);

    free(t);

    t = NULL;

    t = new_tree();

    t = create_from_pre_order(pre2, 4);

    if (t != NULL)
        pre_order(t->root);

    printf("\n");

    destroy_tree(t->root);

    free(t);

    t = NULL;

    return 0;
}
