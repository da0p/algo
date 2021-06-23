#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "linked_list.h"

struct Node
{
    int data;
    struct Node *next;
};

struct List_t
{
    Node *head;
    Node *tail;
    uint32_t size;
    int first;
    int last;
};


List* create_list(void)
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->first = 0;
    list->last = 0;

    if (!list)
        return list;
}

Node* create_node(int val)
{

    Node *tmp = (Node *)malloc(sizeof(Node));

    if (tmp != NULL){

        tmp->data = val;
        tmp->next = NULL;

        return tmp; 
    }
    else
        printf("Failed to allocate memory for new node\r\n");
}

void insert_first(List *list, int val)
{
    Node *p, *tmp;

    p = create_node(val);

    if (list->head == NULL)
    {
        list->head = p;
        list->tail = p;
        list->first = p->data;
        list->last = p->data;
    } else {
        tmp = list->head;
        list->head = p;
        p->next = tmp;
        list->first = p->data;
    }
    list->size++;
}

void insert_last(List *list, int val)
{

    Node *p;

    p = create_node(val);

    if (list->head == NULL) {
        list->head = p;
        list->tail = p;
        list->first = p->data;
        list->last = p->data;
    } else {
        list->tail->next = p;
        list->tail = p;
        list->last = p->data;
    } 
    list->size++;
}

void insert_sorted(List *list, int val)
{

    Node *p;
    Node *current;
    
    current = NULL;
    p = NULL;

    if (list->head == NULL) {
	insert_first(list, val);
    } else {
	for (current = list->head; current != NULL && current->data < val; current = current->next);
	if (current == NULL) insert_last(list, val);
	else insert_before(list, current, val);
    } 
}

void insert_after(List *list, Node *node, int val)
{
    Node *p, *current, *tmp;

    p = create_node(val);

    if (list->head == NULL) {
        insert_last(list, val);
    }
    else {
        if (node == NULL) {
            insert_last(list, val);
        } else {
            for (current = list->head; current != NULL; current = current->next) {
                if (current == node) {
                    if (current == list->tail)
                        insert_last(list, val);
                    else {
                        tmp = current->next;
                        current->next = p;
                        p->next = tmp;
                        list->size++;
                    }
                    return;
                }
            }
        }
    }
}

void insert_before(List *list, Node *node, int val) 
{
    Node *p, *current, *prev;

    current = list->head;

    prev = current;

    p = create_node(val);

    if (list->head == NULL) {
        insert_first(list, val);
    }
    else {
        if (node == NULL) {
            insert_first(list, val);
        } 
        else {
            while (current != NULL) {
                if (current == node) {
                    if (current == list->head)
                        insert_first(list, val);
                    else {
                        prev->next = p;
                        p->next = current;
                        list->size++;
                    }
                    return;
                }
                prev = current;
                current = current->next;
            }
        }
    }
}

Node *search(List *list, int key) 
{
    Node *current = list->head;
    
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

Node *mov_to_head_search(List *list, int key)
{
    Node *current = list->head;
    Node *prev = list->head;

    while (current != NULL) {
        if (current->data == key) {
            if (current != list->head) {
                prev->next = current->next;
                current->next = list->head;
                list->head = current;
                list->first = current->data;
                if (current == list->tail) {
                    list->last = prev->data;
                    list->tail = prev;
                }
            }
            return current;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return NULL;
}

void reverse_w_val(List *list)
{
    Node *current = list->head;

    int *tmp;
    int i = 0;

    if (current != NULL) {
        tmp = (int *) malloc(list->size * sizeof(int));

        for (current = list->head; current != NULL; current = current->next) {
            tmp[i] = current->data;
            i++;
        }
        i--;
        for (current = list->head; current != NULL; current = current->next) {
            current->data = tmp[i--];
        }
        free(tmp);
    }
}

void reverse_w_links(List *list) 
{
    Node *prev, *current, *next;

    next = list->head;
    prev = NULL;
    current = NULL;

    list->tail = list->head;
    list->last = list->tail->data;
    while (next != NULL) {
        prev = current;
        current = next;
        next = next->next;

        current->next = prev;
    }

    list->head = current;
    list->first = current->data;
}

void display(List *list)
{
    Node *current;

    for (current = list->head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\r\n");
}

void display_all(List *list)
{
    Node *current;

    printf("Elements: ");
    for (current = list->head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\r\n");
    printf("first: %d\n", list->first);
    printf("last: %d\n", list->last);
    printf("size: %d\n", list->size);
}

void delete_first(List *list)
{
    Node *tmp = list->head;
    Node *next = tmp->next;

    if (next != NULL){
        list->head = next;
        list->first = next->data;
        list->size--;
    }
    else { 
        list->first = 0;
        list->last = 0;
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    free(tmp);
}

void delete(List *list, Node *node)
{
    Node *current, *prev;

    if (list->head != NULL) {
        current = list->head;
        prev = current;
        while (current != NULL) {
            if (current == node) {
                if (current == list->head) {
                    delete_first(list);
                } else {
                   prev->next = current->next;    
                   free(current);
                   list->size--;
                }
            }
            prev = current;
            current = current->next;
        }
    }
}

void remove_v(List *list, int val)
{
    Node *current = list->head;
    Node *prev = list->head;

    while (current != NULL) {
        if (current->data == val) {
           if (current == list->head) {
               delete_first(list);
               current = list->head;
               prev = list->head;
           } else {
               prev->next = current->next;
               free(current);
               current = prev->next;
               list->size--;
           }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void destroy(List *list)
{
    Node *current = list->head;
    Node *next = current;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
        
    free(list);
}

void concatenate(List **dest, List **src)
{
    if (*dest != NULL && *src != NULL) {
       (*dest)->tail->next = (*src)->head;
       (*dest)->tail = (*src)->tail;
       (*dest)->last = (*src)->last;
       (*dest)->size = (*dest)->size + (*src)->size;
       free(*src);
       *src = *dest;
    }
    else if (*dest == NULL && *src != NULL) {
        *dest = *src;
    }
}

int is_sorted(List *list)
{

    Node *current;

    if (list != NULL)
    {
        if (list->head != NULL) {
            for (current = list->head; current->next != NULL; current = current->next) {
                if (current->data > current->next->data)
                    return -1;
            }
            return 0;
        }
    }
    return -1;
}

List* merge(List **list1, List **list2)
{

    if (!is_sorted(*list1) && !is_sorted(*list2)) {
        List *list3 = create_list();        
        while ((*list1)->head != NULL && (*list2)->head != NULL) {
            if ((*list1)->head->data < (*list2)->head->data) {
                if (list3->head == NULL) {
                    list3->head = (*list1)->head;
                    list3->first = list3->head->data;
                    list3->tail = list3->head;
                    list3->last = list3->tail->data;
                    (*list1)->head = (*list1)->head->next;
                    list3->tail->next = NULL;
                }
                else {
                    list3->tail->next = (*list1)->head;
                    list3->tail = list3->tail->next;
                    list3->last = list3->tail->data;
                    (*list1)->head = (*list1)->head->next;
                    list3->tail->next = NULL;
                }
                list3->size++;
                (*list1)->size--;
            }
            else {
                if (list3->head == NULL) {
                    list3->head = (*list2)->head;
                    list3->first = list3->head->data;
                    list3->tail = list3->head;
                    list3->last = list3->tail->data;
                    (*list2)->head = (*list2)->head->next;
                    list3->tail->next = NULL;
                }
                else {
                    list3->tail->next = (*list2)->head;
                    list3->tail = list3->tail->next;
                    list3->last = list3->tail->data;
                    (*list2)->head = (*list2)->head->next;
                    list3->tail->next = NULL;
                }
                list3->size++;
                (*list2)->size--;
            }
        }

    if ((*list1)->head != NULL) {
        list3->tail->next = (*list1)->head;
        list3->tail = (*list1)->tail;
        list3->last = list3->tail->data;
        list3->size += (*list1)->size;
    }
    if ((*list2)->head != NULL) {
        list3->tail->next = (*list2)->head;
        list3->tail = (*list2)->tail;
        list3->last = list3->tail->data;
        list3->size += (*list2)->size;
    }

    free(*list1);
    free(*list2);

    *list1 = list3;
    *list2 = list3;

    return list3;
    }
}


