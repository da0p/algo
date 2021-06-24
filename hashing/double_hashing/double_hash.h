#ifndef __DOUBLE_HASH_H__
#define __DOUBLE_HASH_H__

typedef struct HTable HTable;

typedef int (*hash_func)(int, int);

HTable* create_htable(int size);

void htable_insert(int val, HTable* htable, hash_func hf);

int htable_search(int val, HTable* htable, hash_func hf);

void htable_display(HTable *htable);

void htable_destroy(HTable *htable);

#endif
