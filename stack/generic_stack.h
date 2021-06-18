#ifndef GENERIC_STACK_H_
#define GENERIC_STACK_H_

#include "generic_linked_list.h"

typedef struct {
    list *list;
} stack;

void stack_new(stack *s, int element_size, free_function free_fn);
void stack_destroy(stack *s);
void stack_push(stack *s, void *element);
void stack_pop(stack *s, void *element);
void stack_peek(stack *s, void *element);
int stack_size(stack *s);
#endif
