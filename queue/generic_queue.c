#include <stdio.h>
#include <stdlib.h>
#include "generic_queue.h"

void queue_new(queue *queue, int element_size, free_function free_fn)
{
    queue->list = malloc(sizeof(list));

    if (queue->list== NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    list_new(queue->list, element_size, free_fn);
}

void queue_destroy(queue *queue)
{
    list_destroy(queue->list);
    free(queue->list);
}

void queue_push(queue *queue, void *element)
{
    list_append(queue->list, element);
}

int queue_size(queue *queue)
{
    return list_size(queue->list);
}

void queue_pop(queue *queue, void *element)
{
    list_pop_head(queue->list, element);
}

void queue_peek(queue *queue, void *element)
{
    list_peek_head(queue->list, element);
}
