#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "hash.h"

HTable create_htable(int size)
{
    HTable htable = (HTable ) malloc(size * sizeof(List*));
    if (htable != NULL) {
        for (int i = 0; i < size; i++)
            htable[i] = create_list();

        return htable;
    }

    return NULL;
}

void htable_insert(int val, HTable htable, hash_func hf)
{
    int i;

    i = hf(val);
    
    insert_sorted(htable[i], val);

}

int htable_search(int val, HTable htable, hash_func hf)
{
    int i;
    Node *node = NULL;

    i = hf(val);

    node = search(htable[i], val); 

    if (node == NULL) return 0;

    return 1;
}

void htable_delete(int val, HTable htable, hash_func hf)
{
    int i;
    Node *node = NULL;

    i = hf(val);
    
    remove_v(htable[i], val);
}

void htable_destroy(HTable htable, int size)
{
    for (int i = 0; i < size; i++)
        destroy(htable[i]);

    free(htable);
}

void htable_display(HTable htable, int size)
{
    for (int i = 0; i < size; i++) {
        printf("Bin %d: ", i);
        display(htable[i]);
    }
}
