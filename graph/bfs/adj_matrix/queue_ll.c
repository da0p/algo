#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "queue_ll.h"

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    Node *head;
    Node *tail;
    uint32_t size;
    uint32_t e;
};


Queue* create_queue(uint32_t size)
{
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

Node* create_node(int val)
{

    Node *tmp = (Node *)malloc(sizeof(Node));

    if (tmp != NULL){

        tmp->data = val;
        tmp->next = NULL;

        return tmp; 
    }
    else {
        printf("Failed to allocate memory for new node\r\n");
        return NULL;
    }
}

int is_empty(Queue *queue)
{
    return (queue->e == 0) ? 1 : 0;
}

int is_full(Queue *queue)
{
    return (queue->e == queue->size) ? 1 : 0;
}

void enqueue(Queue *queue, int val)
{

    Node *p;

    if (queue != NULL) {
        if (!is_full(queue)) {
            p = create_node(val);

            if (queue->head == NULL) {
                queue->head = p;
                queue->tail = p;
            } else {
                queue->tail->next = p;
                queue->tail = p;
            } 
            queue->e++;
        }
        else {
            printf("Queue is full\n");
        }
    }
}


int dequeue(Queue *queue, int *flag)
{
    int r = 0;

    *flag = 0;
    if (queue != NULL) {
        if (!is_empty(queue)) {
            Node *tmp = queue->head;       
            Node *next = tmp->next;

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
            r = tmp->data;
            free(tmp);
        }
        else 
            printf("Queue is empty\n");
    }

    return r;
}


void destroy(Queue *queue)
{
    if (queue != NULL) {
        Node *current = queue->head;
        Node *next = current;

        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        
        free(queue);
    }
}

