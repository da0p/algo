#include <stdio.h>
#include "probe.h"

int hf1(int key) {
    
    return key % 20;
}

int hf2(int ind) {
   return ind; 
}

int hfn(int key, int ind)
{
    return (hf1(key) + hf2(ind)) % 20;
}

int hf3(int ind) {
    
    return ind * ind;
}

int hfn2(int key, int ind)
{
    return (hf1(key) + hf3(ind)) % 20;
}

int main (int argc, char *argv[])
{

    int h[10] = {9, 55, 44, 34, 23, 93, 96, 10, 11, 27};

    HTable *htb;

    htb = create_htable(20);

    for (int i = 0; i < 10; i++) {
        htable_insert(h[i], htb, hfn);
    }

    printf("Linear probing \n\n");

    printf("Linear probing | Search result for 93: %d\n", htable_search(93, htb, hfn));

    htable_display(htb);

    htable_destroy(htb);

    htb = create_htable(20);

    for (int i = 0; i < 10; i++)
        htable_insert(h[i], htb, hfn2);

    printf("Quadratic probing \n\n");
    
    printf("Quadratic probing | Search for 93: %d", htable_search(93, htb, hfn2));

    htable_display(htb);

    htable_destroy(htb);

    return 0;
}

