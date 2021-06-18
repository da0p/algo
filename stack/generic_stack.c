#include <stdio.h>
#include <stdlib.h>
#include "generic_stack.h"

void stack_new(stack *stack, int element_size, free_function free_fn)
{
    stack->list = malloc(sizeof(list));

    if (stack->list== NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    list_new(stack->list, element_size, free_fn);
}

void stack_destroy(stack *stack)
{
    list_destroy(stack->list);
    free(stack->list);
}

void stack_push(stack *stack, void *element)
{
    list_prepend(stack->list, element);
}

int stack_size(stack *stack)
{
    return list_size(stack->list);
}

void stack_pop(stack *stack, void *element)
{
    list_pop_head(stack->list, element);
}

void stack_peek(stack *stack, void *element)
{
    list_peek_head(stack->list, element);
}
