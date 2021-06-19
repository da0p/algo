#include <stdint.h>
#include "common.h"
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

Tree* new_tree(void);

Tree* create_tree(void);

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
