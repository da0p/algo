#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int main(int argc, char *argv[])
{
    
    Tree *t = NULL;

    t = new_tree();

    t = create_tree();

    printf("Pre-order display:\n");
    if (t != NULL)
        pre_order(t->root);
    printf("\n");

    if (t != NULL)
        pre_order_w_stack(t->root);
    printf("\n");

    printf("In-order display:\n");
    if (t != NULL)
        in_order(t->root);
    printf("\n");

    if (t != NULL)
        in_order_w_stack(t->root);
    printf("\n");

    printf("Post-order display\n");
    if (t != NULL)
        post_order(t->root);
    printf("\n");

    if (t != NULL)
        post_order_w_stack(t->root);
    printf("\n");

    printf("Level-order display:\n");
    if (t != NULL)
        level_order(t->root); 
    printf("\n");

    printf("num of leaves: %u, %u\n", t->nnodes, recursive_count_node(t->root));

    printf("total sum: %d\n", recursive_sum(t->root));

    destroy_tree(t->root);

    free(t);

    return 0;
}
