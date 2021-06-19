#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "twothree_tree.h"
#include "queue_ll.h"

#define QUEUE_SIZE_INIT 10
#define COUNT 10

TTNode* create_ttnode(int val)
{
    TTNode *ttnode = (TTNode *) malloc(sizeof(TTNode));

    if (ttnode != NULL) {
        ttnode->first = val;
        ttnode->second = 0;
        ttnode->left = NULL;
        ttnode->middle = NULL;
        ttnode->right = NULL;
        ttnode->stat = 1;

        return ttnode;
    }
    else {
        printf("Failed to allocate memory for node\n");
        return NULL;
    }
}

TTNode* split_node(TTNode *root, TTNode *node, int val)
{
    if (node != NULL) {
        TTNode *ttn1 = NULL;
        TTNode *ttn2 = NULL;
        if (val < node->first) {
            ttn1 = create_ttnode(val);
            ttn2 = create_ttnode(node->second);
            if (node == root) node->stat = 1;
            else node->stat = 3;
            node->left = ttn1;
            node->middle = ttn2;
            node->right = NULL;
            return node;
        }
        else if (val > node->first && val < node->second) {
            ttn1 = create_ttnode(node->first);
            ttn2 = create_ttnode(node->second);
            node->first = val;
            if (node == root) node->stat = 1;
            else node->stat = 3;
            node->left = ttn1;
            node->middle = ttn2;
            node->right = NULL;
            return node;
        }
        else if (val > node->second) {
            ttn1 = create_ttnode(node->first);
            ttn2 = create_ttnode(val);
            if (node == root) node->stat = 1;
            else node->stat = 3;
            node->first = node->second;
            node->left = ttn1;
            node->middle = ttn2;
            node->right = NULL;
            return node;
        }
    }
    
    return NULL;
}

TTNode* insert(TTNode *root, TTNode *node, int val)
{
    if (node == NULL) {
        TTNode *ttnode = create_ttnode(val);
        if (ttnode != NULL)
            return ttnode;
    }
    else {
        if (node->left == NULL && node->middle == NULL && node->right == NULL) {
            if (node->stat == 1) {
               if (node->first < val) {
                   node->second = val;
                   node->stat = 2;
                   return node;
               }
               else if (node->first > val) {
                   node->second = node->first;
                   node->first = val;
                   node->stat = 2;
                   return node;
               }
            }
            else if (node->stat == 2) {
                TTNode *ttn = NULL;
                ttn = split_node(root, node, val);
                return ttn;
            }
        }
        if (node->stat == 1) {
            if (val < node->first) {
                TTNode *tmp = insert(root, node->left, val);
                if (tmp->stat == 3) {
                    node->second = node->first;
                    node->first = tmp->first;
                    node->right = node->middle;
                    node->left = tmp->left;
                    node->middle = tmp->middle;
                    node->stat = 2;
                    free(tmp);
                    return node;
                }
                else if (tmp->stat == 2 || tmp->stat == 1) {
                   node->left = tmp;
                   return node;
                }
            }
            else if (val > node->first) {
                TTNode *tmp = insert(root, node->middle, val);
                if (tmp->stat == 3) {
                    node->second = tmp->first;
                    node->middle = tmp->left;
                    node->right = tmp->middle;
                    node->stat = 2;
                    free(tmp);
                    return node;
                }
                else if (tmp->stat == 2 || tmp->stat == 1) {
                    node->middle = tmp;
                    return node;
                }
            }
        }
        else if (node->stat == 2) {
            if (val < node->first) {
                TTNode *tmp = insert(root, node->left, val);
                if (tmp->stat == 3) {
                    TTNode *pr = create_ttnode(node->second);
                    node->left = tmp;
                    pr->left = node->middle;
                    pr->middle = node->right;
                    node->middle = pr;
                    node->stat = 1;
                    tmp->stat = 1;
                    node->right = NULL;
                    return node;
                }
                else if (tmp->stat == 2 || tmp->stat == 1) {
                    node->left = tmp;
                    return node;
                }
            }
            else if (val > node->first && val < node->second) {
                TTNode *tmp = insert(root, node->middle, val);
                if (tmp->stat == 3) {
                    TTNode *pl = create_ttnode(node->first);
                    TTNode *pr = create_ttnode(node->second);
                    pl->left = node->left;
                    pl->middle = tmp->left;
                    node->left = pl;
                    pr->left = tmp->middle;
                    pr->middle = node->right;
                    node->right = pr;
                    node->first = tmp->first;
                    node->stat = 1;
                    tmp->stat = 1;
                    node->right = NULL;
                    return node;
                }
                else if (tmp->stat == 2 || tmp->stat == 1) {
                    node->middle = tmp;
                    return node;
                }
            }
            else if (val > node->second) {
                TTNode *tmp = insert(root, node->right, val);
                if (tmp->stat == 3) {
                    TTNode *pl = create_ttnode(node->first);
                    pl->left = node->left;
                    pl->middle = node->middle;
                    node->left = pl;
                    node->middle = tmp;
                    node->right = NULL;
                    node->first = node->second;
                    node->stat = 1;
                    tmp->stat = 1;
                    return node;
                }
                else if (tmp->stat == 2 || tmp->stat == 1) {
                    node->right = tmp;
                    return node;
                }
            }
        }
    }

    return NULL;
}

uint32_t recursive_height(TTNode *root)
{
    int x, y, z;

    if (root != NULL) {
        x = recursive_height(root->left);
        y = recursive_height(root->middle);
        z = recursive_height(root->right);

        return x > y ? (x > z ? x + 1 : z + 1) : (y > z ? y + 1 : z + 1);
        }

    return 0;
}

void level_order(TTNode *root)
{
    int flag = 0;
    uint32_t q_size = QUEUE_SIZE_INIT;
    TTNode *tmp = NULL;
    Queue *q = NULL;

    q = create_queue(NULL, QUEUE_SIZE_INIT);

    if (root != NULL) {
        if (root->stat == 1) printf("[%d, -] ", root->first);
        else if (root->stat == 2) printf("[%d, %d] ", root->first, root->second);
        if (is_queue_full(q)) {
            q_size += QUEUE_SIZE_INIT;
            q = create_queue(q, q_size);
        }
        enqueue(q, root);
    }
    else {
        printf("root node is NULL\n");
        return;
    }

    while (!is_queue_empty(q)) {
        tmp = dequeue(q, &flag);
        if (flag) {
            if (tmp->left != NULL) {
                if (tmp->left->stat == 1) printf("[%d, -] ", tmp->left->first);
                else if (tmp->left->stat == 2) printf("[%d, %d] ", tmp->left->first, tmp->left->second);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->left);
            }
            if (tmp->middle != NULL) {
                if (tmp->middle->stat == 1) printf("[%d, -] ", tmp->middle->first);
                else if (tmp->middle->stat == 2) printf("[%d, %d] ", tmp->middle->first, tmp->middle->second);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->middle);
            }

            if (tmp->right != NULL) {
                if (tmp->right->stat == 1) printf("[%d, -] ", tmp->right->first);
                else if (tmp->right->stat == 2) printf("[%d, %d] ", tmp->right->first, tmp->right->second);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->right);
            }
        }
    }
}

void pre_order(TTNode *root) {
    if (root != NULL) {
        if (root->stat == 1) {
            printf("[%d, -] ", root->first);
        }
        else if (root->stat == 2) {
            printf("[%d, %d] ", root->first, root->second);
        }
        pre_order(root->left);
        pre_order(root->middle);
        pre_order(root->right);
    }
}

void in_order(TTNode *root, int space) {
    
    if (root == NULL)
        return;

    space += COUNT;

    in_order(root->left, space);
    printf("\n");
   for (int i = COUNT; i < space; i++)
        printf(" ");
    if (root->stat == 1) printf("[%d, -]\n", root->first);
    else if (root->stat == 2) printf("[%d, %d]\n", root->first, root->second);

    in_order(root->middle, space);
    printf("\n");
    in_order(root->right, space);
}
