#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct CirList {
    struct Node *head;
    struct Node *last;
};

struct CirList* create_cir_list(void)
{
    struct CirList *cir = (struct CirList *)malloc(sizeof(struct CirList));

    if (cir != NULL) {
        cir->head = NULL;
        cir->last = NULL;
        return cir;
    }
    else return NULL;
}

struct Node* create_node(int val)
{
    struct Node *tmp;

    tmp = (struct Node*) malloc(sizeof(struct Node));

    if (tmp != NULL) {
        tmp->data = val;
        tmp->next = NULL;
        return tmp;
    }
    else return NULL;
}

void add(struct CirList *cir, int val)
{
    struct Node *tmp = create_node(val);

    if (cir->head == NULL) {
        cir->head = tmp;
        cir->last = cir->head;
        cir->last->next = cir->head;
    } else {
        cir->last->next = tmp;
        cir->last = cir->last->next;
        cir->last->next = cir->head;
    }
}

void delete(struct CirList *cir)
{
    struct Node *tmp;

    if (cir != NULL) {
        if (cir->head != NULL) {
            if (cir->head->next != cir->head){
                tmp = cir->head;
                cir->head = cir->head->next;
                cir->last->next = cir->head;
                free(tmp);
            }
            else {
                free(cir->head);
                cir->head = NULL;
                cir->last = NULL;
            }
        }
    }
}

void display(struct CirList *cir) 
{
    struct Node *cur = cir->head;

    if (cur != NULL) {
        do {
            printf("%d ", cur->data);
            cur = cur->next;
        } while (cur != cir->head);
        printf("\n");
    }
}

void destroy(struct CirList *cir)
{
    struct Node *next;
    struct Node *cur = cir->head;
    if (cur != NULL) {
        do {
            next = cur->next;
            free(cur);
            cur = next;
        } while (cur != cir->head);
    }
    free(cir);
    cir = NULL;
}

int main(int argc, char *argv[])
{
    struct CirList *cir = create_cir_list();

    add(cir, 5);

    add(cir, 6);

    add(cir, 7);

    display(cir);

    delete(cir);

    display(cir);

    delete(cir);

    display(cir);

    delete(cir);

    display(cir);

    destroy(cir); 

    return 0;
     
}
