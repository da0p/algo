#include "common.h"

#ifndef __TWOTHREE_TREE_H__
#define __TWOTHREE_TREE_H__

typedef struct TTNode TTNode;

TTNode* insert(TTNode *root, TTNode *node, int val);

void level_order(TTNode *root);

void pre_order(TTNode *root);

void in_order(TTNode *root, int space);

#endif
