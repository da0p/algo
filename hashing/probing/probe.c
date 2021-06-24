#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "probe.h"

struct HTable
{
    int size;
    int *table;
    int *flags;
};

HTable* create_htable(int size)
{
    HTable *htb = (HTable*) malloc(sizeof(HTable));

    if (htb != NULL) {
        htb->size = size;
        htb->table = (int *) calloc(size, sizeof(int));
        htb->flags = (int *) calloc(size, sizeof(int));

        if (htb->table != NULL && htb->flags != NULL) {
            return htb;
        }
    }

    return NULL;
}

void htable_insert(int val, HTable *htable, hash_func hf)
{
    int i, k = 0;

    do {
        i = hf(val, k);
        //printf("val = %d, k = %d, i = %d\n", val, k, i);
        k++;
    } while(htable->flags[i]);

    htable->table[i] = val;
    htable->flags[i] = 1;
}

int htable_search(int val, HTable* htable, hash_func hf)
{
    int i, k = 0;

    do {
        i = hf(val, k);

        if (htable->flags[i] == 0) return 0;

        k++;

    }
    while (htable->flags[i] != 0 && htable->table[i] != val);

    return 1;
}

void htable_display(HTable *htable)
{
    printf("\n\tHash Table:\n\n");
    printf("\tKeys \t\t Flags \n");
    for (int i = 0; i < htable->size; i++) {
        printf("\t%d \t\t %d \n\n", htable->table[i], htable->flags[i]);
    }
    printf("\n");
}

void htable_destroy(HTable *htable)
{
    free(htable->flags);
    free(htable->table);
    free(htable);
}
