#ifndef __COMMON_H__
#define __COMMON_H__

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

#endif
