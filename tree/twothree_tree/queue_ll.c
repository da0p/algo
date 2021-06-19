#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "queue_ll.h"

typedef struct QNode {
    TTNode *node;
    struct QNode *next;
} QNode;

struct Queue
{
    QNode *head;
    QNode *tail;
    uint32_t size;
    uint32_t e;
};

Queue* create_queue(Queue *q, uint32_t size)
{

    if (q == NULL) {
        Queue *queue = (Queue *)malloc(sizeof(Queue));
        if (queue != NULL) {
            queue->head = NULL;
            queue->tail = NULL;
            queue->size = size;
            queue->e = 0;

            return queue;
        }
        else {
            printf("Failed to allocate memory for new queue\n");
            return NULL;
        }
    }
    else {
        printf("Resize queue's size to %u\n", size);
        q->size = size;
        return q;
        }
}

QNode* create_queue_node(TTNode *root)
{

    QNode *tmp = (QNode *)malloc(sizeof(QNode));

    if (tmp != NULL){

        tmp->node = root;
        tmp->next = NULL;

        return tmp; 
    }
    else {
        printf("Failed to allocate memory for new node\r\n");
        return NULL;
    }
}

int is_queue_empty(Queue *queue)
{
    return (queue->e == 0) ? 1 : 0;
}

int is_queue_full(Queue *queue)
{
    return (queue->e == queue->size) ? 1 : 0;
}

int enqueue(Queue *queue, TTNode *root)
{

    QNode *p;

    if (queue != NULL) {
        if (!is_queue_full(queue)) {
            p = create_queue_node(root);

            if (queue->head == NULL) {
                queue->head = p;
                queue->tail = p;
            } else {
                queue->tail->next = p;
                queue->tail = p;
            } 
            queue->e++;
            return 1;
        }
        else {
            printf("Queue is full\n");
            return 0;
        }
    }
    return 0;
}


TTNode* dequeue(Queue *queue, int *flag)
{
    TTNode *r = NULL;

    *flag = 0;
    if (queue != NULL) {
        if (!is_queue_empty(queue)) {
            QNode *tmp = queue->head;       
            QNode *next = tmp->next;

            if (next != NULL){
                queue->head = next;
                queue->e--;
            }
            else { 
                queue->head = NULL;
                queue->tail = NULL;
                queue->e = 0;
            }
            *flag = 1;
            r = tmp->node;
            free(tmp);
        }
        else 
            printf("Queue is empty\n");
    }

    return r;
}


void destroy_queue(Queue *queue)
{
    if (queue != NULL) {
        QNode *current = queue->head;
        QNode *next = current;

        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        
        free(queue);
    }
}

