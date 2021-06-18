#include <stdint.h>

#ifndef __BST_H__
#define __BST_H__

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;
typedef struct Tree 
{
    Node *root;
    uint32_t height;
    uint32_t nnodes;
} Tree;

Tree* new_tree(void);

Tree* create_bst(void);

Node* rinsert(Node *root, int key);

Node* search(Node *root, int key);

Node* rsearch(Node *root, int key);

Tree* create_from_pre_order(int *pre, uint32_t size);

Node* delete(Node **root, Node *l, int key);

void pre_order(Node *root);

void pre_order_w_stack(Node *root);

void in_order(Node *root);

void in_order_w_stack(Node *root);

void post_order(Node *root);

void post_order_w_stack(Node *root);

void level_order(Node *root);

uint32_t recursive_count_node(Node *root);

int recursive_sum(Node *root);

uint32_t recursive_height(Node *root);

void destroy_tree(Node *root);

#endif
