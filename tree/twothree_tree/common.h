#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct TTNode 
{
    int first;
    int second;

    struct TTNode *left;
    struct TTNode *middle;
    struct TTNode *right;

    int stat;
}TTNode;
#endif
