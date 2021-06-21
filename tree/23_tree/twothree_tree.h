#include "common.h"

#ifndef __TWOTHREE_TREE_H__
#define __TWOTHREE_TREE_H__

typedef struct TTNode TTNode;

TTNode* insert(TTNode *root, TTNode *node, int val);

TTNode* delete(TTNode **root, TTNode *ndoe, int key);

void destroy_tt_tree(TTNode *root);

TTNode* search(TTNode *root, int key);

void level_order(TTNode *root);

void pre_order(TTNode *root);

void in_order(TTNode *root, int space);

void post_order(TTNode *root);

#endif
