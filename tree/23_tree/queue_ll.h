#include <stdint.h>
#include "twothree_tree.h"
#include "common.h"

#ifndef __QUEUE_LL_H__
#define __QUEUE_LL_H__

typedef struct Queue Queue;

Queue* create_queue(Queue *q, uint32_t size);

int is_queue_empty(Queue *queue);

int is_queue_full(Queue *queue);

int enqueue(Queue *queue, TTNode *root);

TTNode* dequeue(Queue *queue, int *flag);

void destroy_queue(Queue *queue);

#endif
