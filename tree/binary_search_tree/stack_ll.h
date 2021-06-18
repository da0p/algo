#include <stdint.h>
#include "bst.h"

#ifndef __STACK_LL_H__
#define __STACK_LL_H__

typedef struct Stack Stack;

Stack* create_stack(Stack *s, uint32_t size);

int is_stack_full(Stack *s);

int is_stack_empty(Stack *s);

void push(Stack *s, Node *root, int pflag);

Node* pop(Stack *s, int *flag, int *pflag);

Node* peek(Stack *s, int index, int *flag);

void display(Stack *s);

#endif

