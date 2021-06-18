#ifndef GENERIC_LINKED_LIST_H_
#define GENERIC_LINKED_LIST_H_

typedef void (*free_function)(void *);

typedef void (*list_iterator)(void *);

typedef struct list_node_t {
    void *data;
    struct list_node_t *next;
} list_node;

typedef struct list {
    int length;
    int element_size;
    list_node *head;
    list_node *tail;
    free_function free_fn;
} list;

void list_new(list *list, int element_size, free_function free_fn);

void list_append(list *list, void *data);

void list_prepend(list *list, void *data);

void list_destroy(list *list);

int list_size(list *list);

void list_for_each(list *list, list_iterator iterator);

void list_peek_head(list *list, void *element);

void list_pop_head(list *list, void *element);

void list_peek_tail(list *list, void *element);

void list_pop_tail(list *list, void *element);

#endif
