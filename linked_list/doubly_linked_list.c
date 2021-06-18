#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct DoublyCirList {
    struct Node *head;
    struct Node *tail;
};

struct DoublyCirList* create_doubly_cir_list(void)
{
    struct DoublyCirList *dcir = (struct DoublyCirList *)malloc(sizeof(struct DoublyCirList));

    if (dcir != NULL) {
        dcir->head = NULL;
        dcir->tail = NULL;
        return dcir;
    }
    else 
        return NULL;
}

struct Node* create_node(int val)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    if (node != NULL) {
        node->data = val;
        node->next = NULL;
        node->prev = NULL;
    }
    else return NULL;
}

void add(struct DoublyCirList *dcir, int val) 
{
    struct Node *tmp;

    if (dcir != NULL) {

        tmp = create_node(val);

        if (dcir->head == NULL) {
            dcir->head = tmp;
            dcir->tail = tmp;
            dcir->head->next = dcir->head;
            dcir->head->prev = dcir->head;
            dcir->tail->next = dcir->head;
            dcir->tail->prev = dcir->head;
        }
        else {
            tmp->next = dcir->head;
            tmp->prev = dcir->tail;
            dcir->tail->next = tmp;
            dcir->tail = dcir->tail->next;
            dcir->head->prev = dcir->tail;
        }
    }
}

void delete(struct DoublyCirList *dcir)
{

    struct Node *tmp;

    if (dcir != NULL) {
        if (dcir->head != NULL) {
            if (dcir->head != dcir->head->next) {
                tmp = dcir->head;
                dcir->head = dcir->head->next;
                dcir->tail->next = dcir->head;
                dcir->head->prev = dcir->tail;
                free(tmp);
            } else {
                free(dcir->head);
                dcir->head = NULL;
                dcir->tail = NULL;
            }
        }
    }
}

void destroy(struct DoublyCirList *dcir)
{
    struct Node *next, *cur;

    if (dcir != NULL) {
        if (dcir->head != NULL) {
            cur = dcir->head;
            do {
                next = cur->next;
                free(cur);
                cur = next;
            } while (cur != dcir->head);
        }
        free(dcir);
    }

}

void display(struct DoublyCirList *dcir)
{
    struct Node* cur;

    if (dcir != NULL) {
        if (dcir->head != NULL) {
            cur = dcir->head;
            do {
                printf("%d ", cur->data);
                cur = cur->next;
            } while (cur != dcir->head);
        printf("\n");
        }
    }
}

int main(int argc, char *argv[]) 
{
    struct DoublyCirList *dcr;

    dcr = create_doubly_cir_list();

    add(dcr, 4);

    add(dcr, 5);

    add(dcr, 7);

    display(dcr);

    delete(dcr);

    display(dcr);

    delete(dcr);

    display(dcr);

    delete(dcr);

    display(dcr);

    destroy(dcr);

    dcr = NULL;
}
