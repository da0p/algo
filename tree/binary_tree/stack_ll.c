#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack_ll.h"

typedef struct SNode 
{
    Node *root;
    struct SNode *next;
    int pflag;
}SNode;

struct Stack
{
    SNode *head;
    int size;
    int e;
};

Stack* create_stack(Stack *s, uint32_t size) 
{
    if (size < 1) {
        printf("Invalid size\n");
        return NULL;
    }

    if (s == NULL) {

        Stack *stack = (Stack *) malloc (sizeof(Stack));

        if (stack != NULL) {
            stack->head = NULL;
            stack->e = 0;
            stack->size = size;
            return stack;
        }
        else {
            printf("Failed to allocate memory\n");
            return NULL;
        }
    }
    else {
        printf("Resize stack's size to %u\n", size);
        s->size = size;
        return s;
    }
}

SNode* create_stack_node(Node *root) 
{
    SNode *node = (SNode *) malloc(sizeof(SNode));

    if (node != NULL) {
        node->root = root;
        node->next = NULL;
        node->pflag = 0;
        return node;
    }
    else {
        printf("Failed to allocate memory\n");
        return NULL;
    }
}

int is_stack_full(Stack *s) 
{
    if (s->head != NULL) {
        return (s->e == s->size) ? 1 : 0;
    }

    return 0;
}

int is_stack_empty(Stack *s)
{
    return (s->head == NULL) ? 1 : 0;
}

void push(Stack *s, Node *root, int pflag)
{
    if (s != NULL) {
        SNode *tp = create_stack_node(root);
        if (is_stack_full(s)) {
            printf("Stack overflow\n"); 
        }
        else {
            tp->pflag = pflag;
            tp->next = s->head;
            s->head = tp;
            s->e++;
        }
    }
}

Node* pop(Stack *s, int *flag, int *pflag) {
    *flag = 0;
    if (s != NULL) {
        if (is_stack_empty(s)) {
            printf("Stack undeflow\n");
            *flag = 0;
            return NULL;
        }
        else {
            SNode *tp = s->head;
            Node *r = s->head->root;

            s->head = s->head->next;

            *pflag = tp->pflag;

            free(tp);

            tp = NULL;

            *flag = 1;
            
            s->e--;

            return r;
        }
    }

    return NULL;
}

Node* peek(Stack *s, int index, int *flag) {
    *flag = 0;

    if (index > s->size - 1 || index < 0) {
        printf("Invalid index\n");
        return NULL;
    }

    if (is_stack_empty(s)) {
        printf("Stack underflow\n");
        *flag = 0;
        return NULL;
    }
    else {
        SNode *cur = s->head;
        int i;

        for (i = 0; i < index; i++) cur = cur->next;

        *flag = 1;

        return cur->root;
    }
}

void display(Stack *s)
{
    SNode *cur;

    if (s->head != NULL) {
        for (cur = s->head; cur != NULL; cur = cur->next) {
            printf("%p ", cur->root);
        }
        printf("\n");
    }
}

void destroy(Stack *s)
{
    SNode *tp, *next;

    if (s != NULL) {
        tp = s->head;
        while (tp != NULL) {
            next = tp->next;
            free(tp);
            tp = next;
        }
        free(s);
    }
}
