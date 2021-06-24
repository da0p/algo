#include <stdio.h>
#include "double_hash.h"

#define SIZE 10
#define PRIME 7

int hf1(int key) {
    
    return key % SIZE;
}

int hf2(int key) {
   return PRIME - (key % PRIME); 
}

int hfn(int key, int ind)
{
    return (hf1(key) + ind * hf2(key)) % SIZE;
}


int main (int argc, char *argv[])
{

    int h[10] = {9, 55, 44, 34, 23, 93, 96, 10, 11, 27};

    HTable *htb;

    htb = create_htable(SIZE);

    for (int i = 0; i < 10; i++) {
        htable_insert(h[i], htb, hfn);
    }

    printf("Double Hash\n\n");

    printf("Search result for 93: %d\n", htable_search(93, htb, hfn));

    htable_display(htb);

    htable_destroy(htb);

    return 0;
}

