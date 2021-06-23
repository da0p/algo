#ifndef __HASH_H__
#define __HASH_H__
#include "linked_list.h"

typedef List** HTable;

typedef int (*hash_func)(int);

HTable create_htable(int size);

void htable_insert(int val, HTable htable, hash_func hf);

int htable_search(int val, HTable htable, hash_func hf);

void htable_delete(int val, HTable htable, hash_func hf);

void htable_destroy(HTable htable, int size);

void htable_display(HTable htable, int size);

#endif
