#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_linked_list.h"

void list_new(list *list, int element_size, free_function free_fn)
{
    list->length = 0;
    list->element_size = element_size;
    list->head = NULL;
    list->tail = NULL;
    list->free_fn = free_fn;
}

void list_append(list *list, void *data)
{
    list_node *tmp;

    tmp = malloc(sizeof(list_node));
    tmp->data = malloc(sizeof(list->element_size));
    memcpy(tmp->data, data, list->element_size);
    tmp->next = NULL;

    if (list->head == NULL) {
        list->head = tmp;
        list->tail = tmp;
    } else {
        list->tail->next = tmp;
        list->tail = tmp;
    }

    list->length++;
}

void list_prepend(list *list, void *data)
{
    list_node *tmp;
    
    tmp = malloc(sizeof(list_node));
    tmp->data = malloc(sizeof(list->element_size));
    memcpy(tmp->data, data, list->element_size);
    tmp->next = NULL;

    if (list->head == NULL) {
        list->head = tmp;
        list->tail = tmp;
    } else {
        tmp->next = list->head;
        list->head = tmp;
    }

    list->length++;
}

void list_destroy(list *list)
{
    list_node *tmp = NULL;
    list_node *it = list->head;

    while (it != NULL) {
        tmp = it;
        it = it->next;

        if (list->free_fn != NULL) {
            list->free_fn(tmp->data);
        } else {
            free(tmp->data);
        }
        free(tmp);
    }

    list->length = 0;
    list->element_size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->free_fn = NULL;
}

int list_size(list *list)
{
    return list->length;
}

void list_for_each(list *list, list_iterator iterator)
{
    list_node *it = list->head;

    while (it != NULL) {
        iterator(it->data);
        it = it->next;
    }
}

void list_peek_head(list *list, void *element)
{
    if (list->head != NULL) {
        memcpy(element, list->head->data, list->element_size);
    } else {
        printf("No element to peek\n");
    }
}

void list_pop_head(list *list, void *element)
{
    list_node *tmp = NULL;
    
    if (list->head != NULL) {
        memcpy(element, list->head->data, list->element_size);
        tmp = list->head;
        list->head = list->head->next;
        if (list->free_fn != NULL) {
            list->free_fn(tmp->data);
        } else {
            free(tmp->data);
        }
        free(tmp);
        list->length--;
    } else {
        printf("ERROR! No element to pop\n");
        exit(1);
    }
}

void list_peek_tail(list *list, void *element)
{
    list_node *tmp = NULL;

    if (list->head != NULL) {
        memcpy(element, list->tail->data, list->element_size);
    } else {
        printf("No element to peek\n");
    }
}

void list_pop_tail(list *list, void *element)
{
    list_node *it = NULL;
    list_node *prev = NULL;

    if (list->head != NULL) {
        memcpy(element, list->tail->data, list->element_size);

        it = list->head;
        while (it->next != NULL) {
            prev = it;
            it = it->next;
        }
        prev->next = NULL;
        list->tail = prev;
        if (list->free_fn != NULL) {
            list->free_fn(it->data);
        } else {
            free(it->data);
        }
        free(it);
        list->length--;
    } else {
        printf("ERROR! No element to pop\n");
        exit(1);
    }
}

