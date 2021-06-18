#ifndef GENERIC_QUEUE_H_
#define GENERIC_QUEUE_H_

#include "generic_linked_list.h"

typedef struct {
    list *list;
} queue;

void queue_new(queue *s, int element_size, free_function free_fn);
void queue_destroy(queue *s);
void queue_push(queue *s, void *element);
void queue_pop(queue *s, void *element);
void queue_peek(queue *s, void *element);
int queue_size(queue *s);
#endif
