#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct Node Node;

typedef struct List_t List;

List* create_list(void);

void insert_first(List *list, int val);

void insert_last(List *list, int val);

void insert_after(List *list, Node *node, int val);

void insert_before(List *list, Node *node, int val);

void insert_sorted(List *list, int val);

Node *search(List *list, int key);

Node *mov_to_head_search(List *list, int key);

void reverse_w_val(List *list);

void reverse_w_links(List *list);

void display(List *list);

void display_all(List *list);

void delete_first(List *list);

void delete(List *list, Node *node);

void remove_v(List *list, int val);

void destroy(List *list);

void concatenate(List **dest, List **src);

int is_sorted(List *list);

List* merge(List **list1, List **list2);

#endif
