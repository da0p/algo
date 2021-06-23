#include <stdio.h>
#include "linked_list.h"
#include "hash.h"

int hfcn(int key)
{
    return key % 10;
}

int main (int argc, char *argv[])
{
    int A[10] = {5, 19, 25, 4, 10, 23, 44, 92, 75, 21};

    HTable htb;

    htb = create_htable(10);

    for (int i = 0; i < 10; i++)
        htable_insert(A[i], htb, hfcn);

    htable_display(htb, 10);

    printf("\nAfter delete 5\n");

    htable_delete(5, htb, hfcn);

    htable_display(htb, 10);

    htable_destroy(htb, 10);

    htb = NULL;

    return 0;
}

