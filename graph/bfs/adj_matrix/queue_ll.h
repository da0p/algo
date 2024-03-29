#include <stdint.h>

#ifndef __QUEUE_LL_H__
#define __QUEUE_LL_H__

typedef struct Node Node;

typedef struct Queue Queue;

Queue* create_queue(uint32_t size);

int is_empty(Queue *queue);

int is_full(Queue *queue);

void enqueue(Queue *queue, int val);

int dequeue(Queue *queue, int *flag);

void destroy(Queue *queue);

#endif
