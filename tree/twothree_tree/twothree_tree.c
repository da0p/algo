#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "twothree_tree.h"
#include "queue_ll.h"

#define QUEUE_SIZE_INIT 10
#define COUNT 10

typedef enum {
    DEFAULT,
    ONE_ELEMENT,
    TWO_ELEMENT,
    SPLITTED_ELEMENT,
    BLANK_LEAF_NODE,
    BLANK_NODE_WITH_MERGED_CHILDREN
} Status;

void debug(TTNode *node, char *str) 
{
    if (node->stat == ONE_ELEMENT)
        printf("%s | [%d, -] \n", str, node->first);
    else if (node->stat == TWO_ELEMENT)
        printf("%s | [%d, %d] \n", str, node->first, node->second);
}

TTNode* create_ttnode(int val)
{
    TTNode *ttnode = (TTNode *) malloc(sizeof(TTNode));

    if (ttnode != NULL) {
        ttnode->first = val;
        ttnode->second = 0;
        ttnode->left = NULL;
        ttnode->middle = NULL;
        ttnode->right = NULL;
        ttnode->stat = ONE_ELEMENT;

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
            if (node == root) node->stat = ONE_ELEMENT;
            else node->stat = SPLITTED_ELEMENT;
            node->left = ttn1;
            node->middle = ttn2;
            node->right = NULL;
            return node;
        }
        else if (val > node->first && val < node->second) {
            ttn1 = create_ttnode(node->first);
            ttn2 = create_ttnode(node->second);
            node->first = val;
            if (node == root) node->stat = ONE_ELEMENT;
            else node->stat = SPLITTED_ELEMENT;
            node->left = ttn1;
            node->middle = ttn2;
            node->right = NULL;
            return node;
        }
        else if (val > node->second) {
            ttn1 = create_ttnode(node->first);
            ttn2 = create_ttnode(val);
            if (node == root) node->stat = ONE_ELEMENT;
            else node->stat = SPLITTED_ELEMENT;
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
        // for leaves
        if (node->left == NULL && node->middle == NULL && node->right == NULL) {
            if (node->stat == ONE_ELEMENT) {
               if (node->first < val) {
                   node->second = val;
                   node->stat = TWO_ELEMENT;
                   return node;
               }
               else if (node->first > val) {
                   node->second = node->first;
                   node->first = val;
                   node->stat = TWO_ELEMENT;
                   return node;
               }
            }
            else if (node->stat == TWO_ELEMENT) {
                TTNode *ttn = NULL;
                ttn = split_node(root, node, val);
                return ttn;
            }
        }
        
        if (node->stat == ONE_ELEMENT) {
            if (val < node->first) {
                TTNode *tmp = insert(root, node->left, val);
                if (tmp->stat == SPLITTED_ELEMENT) {
                    node->second = node->first;
                    node->first = tmp->first;
                    node->right = node->middle;
                    node->left = tmp->left;
                    node->middle = tmp->middle;
                    node->stat = TWO_ELEMENT;
                    free(tmp);
                    return node;
                }
                else if (tmp->stat == TWO_ELEMENT || tmp->stat == ONE_ELEMENT) {
                   node->left = tmp;
                   return node;
                }
            }
            else if (val > node->first) {
                TTNode *tmp = insert(root, node->middle, val);
                if (tmp->stat == SPLITTED_ELEMENT) {
                    node->second = tmp->first;
                    node->middle = tmp->left;
                    node->right = tmp->middle;
                    node->stat = TWO_ELEMENT;
                    free(tmp);
                    return node;
                }
                else if (tmp->stat == TWO_ELEMENT || tmp->stat == ONE_ELEMENT) {
                    node->middle = tmp;
                    return node;
                }
            }
        }
        else if (node->stat == TWO_ELEMENT) {
            if (val < node->first) {
                TTNode *tmp = insert(root, node->left, val);
                if (tmp->stat == SPLITTED_ELEMENT) {
                    TTNode *pm = node->middle;
                    TTNode *pr = node->right;
                    TTNode *pl = split_node(root, node, tmp->first);
                    pl->left->left = tmp->left;
                    pl->left->middle = tmp->middle;
                    free(tmp);
                    pl->middle->left = pm;
                    pl->middle->middle = pr;

                    if (pl == root)
                        pl->stat = ONE_ELEMENT;

                    return pl;

                }
                else if (tmp->stat == TWO_ELEMENT || tmp->stat == ONE_ELEMENT) {
                    node->left = tmp;
                    return node;
                }
            }
            else if (val > node->first && val < node->second) {
                TTNode *tmp = insert(root, node->middle, val);
                if (tmp->stat == SPLITTED_ELEMENT) {
                    TTNode *pl = node->left;
                    TTNode *pr = node->right;
                    TTNode *pm = split_node(root, node, tmp->first);
                    pm->left->left = pl;
                    pm->left->middle = tmp->left;
                    pm->middle->left = tmp->middle;
                    pm->middle->middle = pr;
                    free(tmp);
                    if (pm == root)
                        pm->stat = ONE_ELEMENT;
                    return pm;
                }
                else if (tmp->stat == TWO_ELEMENT || tmp->stat == ONE_ELEMENT) {
                    node->middle = tmp;
                    return node;
                }
            }
            else if (val > node->second) {
                TTNode *tmp = insert(root, node->right, val);
                if (tmp->stat == SPLITTED_ELEMENT) {
                    TTNode *pl = node->left;
                    TTNode *pm = node->middle;
                    TTNode *pr = split_node(root, node, tmp->first);
                    pr->left->left = pl;
                    pr->left->middle = pm;
                    pr->middle->left = tmp->left;
                    pr->middle->middle = tmp->middle;
                    free(tmp);
                    if (pr == root)
                        pr->stat = ONE_ELEMENT;
                    return pr;
                }
                else if (tmp->stat == TWO_ELEMENT || tmp->stat == ONE_ELEMENT) {
                    node->right = tmp;
                    return node;
                }
            }
        }
    }

    return NULL;
}

TTNode* search(TTNode *root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->stat == ONE_ELEMENT && root->first == key)
    {
        return root;
    }

    if (root->stat == TWO_ELEMENT && (root->first == key || root->second == key)) {
            return root;
    }
    if (root->stat == TWO_ELEMENT) {
        if (key < root->first) {
            return search(root->left, key);
        }
        else if (key > root->first && key < root->second) {
            return search(root->middle, key);
        }
        else if (key > root->second) {
            return search(root->right, key);
        }
    }

    else if (root->stat == ONE_ELEMENT) {
        if (key < root->first) {
            return search(root->left, key);
        }
        else if (key > root->first) {
            return search(root->middle, key);
        }
    }
    return NULL;
}

TTNode* in_order_pre(TTNode *node)
{
    TTNode *n = node;
    n = n->left;
    while (n != NULL && (n->right != NULL || n->middle != NULL)) {
        if (n->right != NULL) n = n->right;
        else if (n->middle != NULL) n = n->middle;
    }
    return n;
}

TTNode* in_order_suc(TTNode *node)
{
    TTNode *n = node;
    if (n->stat == TWO_ELEMENT)
        n = n->right;
    else if (n->stat == ONE_ELEMENT)
        n = n->middle;
    while (n != NULL && (n->left != NULL || n->middle != NULL)) {
        if (n->left != NULL) n = n->left;
        else if (n->middle != NULL) n = n->middle;
    }
    return n;
}

TTNode* delete(TTNode **root, TTNode *node, int key)
{
    if (*root == NULL)
        return NULL;
    
    if (node != NULL) {
        if ((key == node->first && node->stat == ONE_ELEMENT) || 
            ((key == node->first || key == node->second) && node->stat == TWO_ELEMENT)) {
            printf("External node | Found key = %d\n", key);
            /* case 1: if the node found is a leaf node*/
            if (node->left == NULL && node->middle == NULL && node->right == NULL) {
                /* case 1.1: node found with two elements */
                if (node->stat == TWO_ELEMENT) {
                    if (key == node->second) {
                        node->second = 0;
                        node->stat = ONE_ELEMENT;
                    }
                    else if (key == node->first) {
                        node->first = node->second;
                        node->stat = ONE_ELEMENT;
                        node->second = 0;
                    }
                    return node;
                }
                /* case 1.2: node found with one element */
                else if (node->stat == ONE_ELEMENT) {
                    /* change node status and delegated to parent to process */
                    node->stat = BLANK_LEAF_NODE; 
                    node->first = 0;
                    node->second = 0;
                    if (node == *root) {
                        free(*root);
                        *root = NULL;
                    }
                    return node;
                }
            }
            /* case 2: if the node found is an internal node */
            else {
                printf("Internal node | Found key = %d\n",key);
                /* case 2.1: the node has two elements */
                if (node->stat == TWO_ELEMENT) {
                    if (key == node->second) {
                        TTNode *iosn = in_order_suc(node);
                        if (iosn->stat == TWO_ELEMENT) {
                            node->second = iosn->first;
                            iosn->first = iosn->second;
                            iosn->stat = ONE_ELEMENT;
                            return node;
                        }
                        else if (iosn->stat == ONE_ELEMENT) {
                            if (node->right != iosn) {
                                node->second = iosn->first;
                                iosn->second = 0;
                                node->right =  delete(root, node->right, iosn->first);
                                return node;
                            }
                            else {
                                if (node->middle->stat == ONE_ELEMENT) {
                                    node->second = 0;
                                    node->stat = ONE_ELEMENT;
                                    node->middle->second = iosn->first;
                                    node->middle->stat = TWO_ELEMENT;
                                    free(iosn);
                                    node->right = NULL;
                                    return node;
                                }
                                else if (node->middle->stat == TWO_ELEMENT) {
                                    node->second = node->middle->second;
                                    node->middle->stat = ONE_ELEMENT;
                                    node->middle->second = 0;
                                    node->stat = TWO_ELEMENT;
                                    return node;
                                }
                            }
                        }
                    }
                    else if (key == node->first) {
                        TTNode *iopn = in_order_pre(node);
                        if (iopn->stat == TWO_ELEMENT) {
                            node->first = iopn->second;
                            iopn->second = 0;
                            iopn->stat = ONE_ELEMENT;
                            return node;
                        }
                        if (iopn->stat == ONE_ELEMENT) {
                            if (node->left != iopn) {
                                node->first = iopn->first;
                                iopn->second = 0;
                                /* this is definitely a leaf node */
                                node->left = delete(root, node->left, iopn->first); 
                                return node;
                            }
                            else {
                                if (node->middle->stat == ONE_ELEMENT) {
                                    node->first = node->second;
                                    node->second = 0;
                                    node->stat = ONE_ELEMENT;
                                    iopn->second = node->middle->first;
                                    iopn->stat = TWO_ELEMENT;
                                    node->middle = node->right;
                                    node->right = NULL;
                                    return node;
                                }
                                else if (node->middle->stat == TWO_ELEMENT) {
                                    node->first = node->middle->first;
                                    node->middle->first = node->middle->second;
                                    node->middle->second = 0;
                                    node->middle->stat = ONE_ELEMENT;
                                    return node;
                                }
                            }
                        }
                    }
                }
                /* case 2.2: the node has only one element */
                else if (node->stat == ONE_ELEMENT) {
                    TTNode *iopn = in_order_pre(node);
                    debug(node, "node");
                    debug(iopn, "in_order_pre"); 
                    if (iopn->stat == TWO_ELEMENT) {
                        node->first = iopn->second;
                        iopn->second = 0;
                        iopn->stat = ONE_ELEMENT;
                        return node;
                    }
                    else if (iopn->stat == ONE_ELEMENT) {
                        if (node->left != iopn) {
                            node->first = iopn->first;
                            node->left = delete(root, node->left, iopn->first);
                            return node;
                        }
                        else {
                            TTNode *pm = node->middle;
                            iopn->second = pm->first;
                            iopn->stat = TWO_ELEMENT;
                            free(pm);
                            node->first = 0;
                            node->second = 0;
                            node->stat = BLANK_NODE_WITH_MERGED_CHILDREN;
                            return node;
                        }
                    }
                }
            }
        }
        /* if key is not found */
        else {
            if (node->stat == ONE_ELEMENT) {
                if (key < node->first) {
                    TTNode *tmp = delete(root, node->left, key);
                    if (tmp->stat != BLANK_LEAF_NODE && tmp->stat != BLANK_NODE_WITH_MERGED_CHILDREN) {
                        node->left = tmp;
                        return node;
                    }
                    else {
                        if (tmp->stat == BLANK_LEAF_NODE) {
                            if (node->middle->stat == TWO_ELEMENT) {
                                tmp->first = node->first;
                                tmp->stat = ONE_ELEMENT;
                                node->first = node->middle->first;
                                node->middle->first = node->middle->second;
                                node->middle->second = 0;
                                node->middle->stat = ONE_ELEMENT;
                                return node;
                            }
                            else if (node->middle->stat == ONE_ELEMENT) {
                                node->middle->second = node->middle->first;
                                node->middle->first = node->first;
                                node->middle->stat = TWO_ELEMENT;
                                node->first = 0;
                                node->stat = BLANK_NODE_WITH_MERGED_CHILDREN;
                                node->left = node->middle;
                                node->middle = NULL;
                                free(tmp);
                                if (node == *root) {
                                    tmp = node;
                                    node = node->left;
                                    free(tmp);
                                    *root = node;
                                }
                                return node;
                            }
                        }
                        else if (tmp->stat == BLANK_NODE_WITH_MERGED_CHILDREN) {
                            //TODO
                            if (node->middle->stat == TWO_ELEMENT) {
                                tmp->first = node->first;
                                tmp->stat = ONE_ELEMENT;
                                tmp->middle = node->middle->left;
                                node->first = node->middle->first;
                                node->middle->first = node->middle->second;
                                node->middle->second = 0;
                                node->middle->stat = ONE_ELEMENT;
                                node->middle->left = node->middle->middle;
                                node->middle->middle = node->middle->right;
                                node->middle->right = NULL;
                                return node;
                            }
                            else if (node->middle->stat == ONE_ELEMENT) {
                                TTNode *pm = node->middle;
                                if (node != *root) {
                                    tmp->first = node->first;
                                    tmp->second = node->middle->first;
                                    tmp->stat = TWO_ELEMENT;
                                    tmp->middle = pm->left;
                                    tmp->right = pm->middle;
                                    free(pm);
                                    node->first = 0;
                                    node->stat = BLANK_NODE_WITH_MERGED_CHILDREN;
                                    node->right = NULL;
                                    return node;
                                }
                                else {
                                    node->second = pm->first;
                                    node->stat = TWO_ELEMENT;
                                    node->left = tmp->left;
                                    node->middle = pm->left;
                                    node->right = pm->middle;
                                    free(tmp);
                                    free(pm);

                                    return node;
                                }
                            }
                        }
                        
                    }
                }
                else if (key > node->first) {
                    TTNode *tmp = delete(root, node->middle, key);
                    if (tmp->stat != BLANK_LEAF_NODE && tmp->stat != BLANK_NODE_WITH_MERGED_CHILDREN) {
                        node->middle = tmp;
                        return node;
                    }
                    else {
                        if (tmp->stat == BLANK_LEAF_NODE) {
                            if (node->left->stat == TWO_ELEMENT) {
                                node->middle->first = node->first;
                                node->first = node->left->second;
                                node->left->second = 0;
                                node->left->stat = ONE_ELEMENT;
                                return node;
                            }
                            else if (node->left->stat == ONE_ELEMENT) {
                                TTNode *pm = node->middle;
                                node->left->second = node->first;
                                node->left->stat = TWO_ELEMENT;
                                node->first = 0;
                                node->stat = BLANK_NODE_WITH_MERGED_CHILDREN;
                                free(pm);
                                node->middle = NULL;
                                return node;
                            }
                        }
                        else if (tmp->stat == BLANK_NODE_WITH_MERGED_CHILDREN) {
                            //TODO
                            if (node->left->stat == TWO_ELEMENT) {
                                tmp->middle = node->middle->left;
                                tmp->left = node->left->right;
                                tmp->first = node->first;
                                tmp->stat = ONE_ELEMENT;
                                node->first = node->left->second;
                                node->left->second = 0;
                                node->left->right = NULL;
                                return node;
                            }
                            else if (node->left->stat == ONE_ELEMENT) {
                                TTNode *pl = node->left;
                                node->second = node->first;
                                node->first = node->left->first;
                                node->stat = TWO_ELEMENT;
                                node->left = pl->left;
                                node->middle = pl->middle;
                                node->right = tmp->left;
                                free(pl);
                                free(tmp);
                                return node;
                            }
                        }

                    }
                }
            }
            else if (node->stat == TWO_ELEMENT) {
                if (key < node->first) {
                    TTNode *tmp = delete(root, node->left, key);
                    if (tmp->stat != BLANK_LEAF_NODE && tmp->stat != BLANK_NODE_WITH_MERGED_CHILDREN) {
                        node->left = tmp;
                        return node;
                    }
                    else {
                        if (tmp->stat == BLANK_LEAF_NODE) {
                            if (node->middle->stat == TWO_ELEMENT) {
                                tmp->first = node->first;
                                tmp->stat = ONE_ELEMENT;
                                node->first = node->middle->first;
                                node->middle->first = node->middle->second;
                                node->middle->second = 0;
                                node->middle->stat = ONE_ELEMENT;
                                return node;
                            }
                            else if (node->middle->stat == ONE_ELEMENT) {
                                node->middle->second = node->middle->first;
                                node->middle->first = node->first;
                                node->middle->stat = TWO_ELEMENT;
                                node->first = node->second;
                                node->second = 0;
                                node->stat = ONE_ELEMENT;
                                free(tmp);
                                node->left = node->middle;
                                node->middle = node->right;
                                node->right = NULL;
                                return node;
                            }
                        }
                        else if (tmp->stat == BLANK_NODE_WITH_MERGED_CHILDREN) {
                            if (node->middle->stat == TWO_ELEMENT) {
                                tmp->first = node->first;
                                tmp->middle = node->middle->left;
                                tmp->stat = ONE_ELEMENT;
                                node->first = node->middle->first;
                                node->middle->first = node->middle->second;
                                node->middle->second = 0;
                                node->middle->stat = ONE_ELEMENT;
                                node->middle->left = node->middle->middle;
                                node->middle->middle = node->middle->right;
                                node->middle->right = NULL;
                                return node;
                            }
                            else if (node->middle->stat == ONE_ELEMENT) {
                                node->middle->second = node->middle->first;
                                node->middle->first = node->first;
                                node->middle->stat = TWO_ELEMENT;
                                node->middle->right = node->middle->middle;
                                node->middle->middle = node->middle->left;
                                node->middle->left = tmp->left;
                                node->first = node->second;
                                node->second = 0;
                                node->stat = ONE_ELEMENT;
                                free(tmp);
                                node->left = node->middle;
                                node->middle = node->right;
                                node->right = NULL;
                                return node;
                            }
                        }
                    }
                }
                else if (key > node->first && key < node->second) {
                    TTNode *tmp = delete(root, node->middle, key);
                    if (tmp->stat != BLANK_LEAF_NODE && tmp->stat != BLANK_NODE_WITH_MERGED_CHILDREN) {
                        node->middle = tmp;
                        return node;
                    }
                    else {
                        if (tmp->stat == BLANK_LEAF_NODE) {
                            node->left->second = node->first;
                            node->left->stat = TWO_ELEMENT;
                            node->first = node->second;
                            node->second = 0;
                            node->stat = ONE_ELEMENT;
                            free(tmp);
                            node->middle = node->right;
                            node->right = NULL;
                            return node;
                        }
                        else if (tmp->stat == BLANK_NODE_WITH_MERGED_CHILDREN) {
                            if (node->left->stat == TWO_ELEMENT) {
                                tmp->first = node->first;
                                tmp->stat = ONE_ELEMENT;
                                tmp->middle = tmp->left;
                                tmp->left = node->left->right;
                                node->first = node->left->second;
                                node->left->second = 0;
                                node->left->stat = ONE_ELEMENT;
                                node->left->right = NULL;
                                return node;
                            }
                            else if (node->right->stat == TWO_ELEMENT) {
                                tmp->first = node->second;
                                tmp->stat = ONE_ELEMENT;
                                tmp->middle = node->right->left;
                                node->second = node->right->first;
                                node->right->first = node->right->second;
                                node->right->left = node->right->middle;
                                node->right->middle = node->right->right;
                                node->right->right = NULL;
                                return node;
                            }
                            else if (node->right->stat == ONE_ELEMENT) {
                                node->right->second = node->right->first;
                                node->right->first = node->first;
                                node->right->stat = TWO_ELEMENT;
                                node->right->right = node->right->middle;
                                node->right->middle = node->right->left;
                                node->right->left = tmp->left;
                                node->stat = ONE_ELEMENT;
                                free(tmp);
                                node->middle = node->right;
                                node->right = NULL;
                                return node;
                            }
                        }
                    }
                        
                }// key > node->first && key < node->second close
                else if (key > node->second) {
                    TTNode *tmp = delete(root, node->right, key);
                    if (tmp->stat != BLANK_LEAF_NODE && tmp->stat != BLANK_NODE_WITH_MERGED_CHILDREN) {
                        node->right = tmp;
                        return node;
                    }
                    else {
                        if (tmp->stat == BLANK_LEAF_NODE) {
                            if (node->middle->stat == TWO_ELEMENT) {
                                tmp->first = node->second;
                                tmp->stat = ONE_ELEMENT;
                                node->second = node->middle->second;
                                node->middle->second = 0;
                                node->middle->stat = ONE_ELEMENT;
                                return node;
                            }
                            else if (node->middle->stat == ONE_ELEMENT) {
                                node->middle->second = node->second;
                                node->middle->stat = TWO_ELEMENT;
                                node->second = 0;
                                free(tmp);
                                node->right = NULL;
                                node->stat = ONE_ELEMENT;
                                return node;
                            }
                        }
                        else if (tmp->stat == BLANK_NODE_WITH_MERGED_CHILDREN) {
                            if (node->middle->stat == TWO_ELEMENT) {
                                tmp->first = node->second;
                                tmp->stat = ONE_ELEMENT;
                                tmp->middle = tmp->left;
                                tmp->left = node->middle->right;
                                node->second = node->middle->second;
                                node->middle->stat = ONE_ELEMENT;
                                node->middle->right = NULL;
                                return node;
                            }
                            else if (node->middle->stat == ONE_ELEMENT) {
                                node->middle->second = node->second;
                                node->middle->right = tmp->left;
                                node->middle->stat = TWO_ELEMENT;
                                node->second = 0;
                                node->stat = ONE_ELEMENT;
                                free(tmp);
                                node->right = NULL;
                                return node;
                            }
                        }
                    }
                }// key > node->second close case
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
        if (root->stat == ONE_ELEMENT) printf("[%d, -] ", root->first);
        else if (root->stat == TWO_ELEMENT) printf("[%d, %d] ", root->first, root->second);
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
                if (tmp->left->stat == ONE_ELEMENT) printf("[%d, -] ", tmp->left->first);
                else if (tmp->left->stat == TWO_ELEMENT) printf("[%d, %d] ", tmp->left->first, tmp->left->second);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->left);
            }
            if (tmp->middle != NULL) {
                if (tmp->middle->stat == ONE_ELEMENT) printf("[%d, -] ", tmp->middle->first);
                else if (tmp->middle->stat == TWO_ELEMENT) printf("[%d, %d] ", tmp->middle->first, tmp->middle->second);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->middle);
            }

            if (tmp->right != NULL) {
                if (tmp->right->stat == ONE_ELEMENT) printf("[%d, -] ", tmp->right->first);
                else if (tmp->right->stat == TWO_ELEMENT) printf("[%d, %d] ", tmp->right->first, tmp->right->second);
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
        if (root->stat == ONE_ELEMENT) {
            printf("[%d, -] ", root->first);
        }
        else if (root->stat == TWO_ELEMENT) {
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
    if (root->stat == ONE_ELEMENT) printf("[%d, -]\n", root->first);
    else if (root->stat == TWO_ELEMENT) printf("[%d, %d]\n", root->first, root->second);
    else printf("[-, -]\n");

    in_order(root->middle, space);
    printf("\n");
    in_order(root->right, space);
}

void post_order(TTNode *root)
{
    if (root != NULL) {
        post_order(root->left);
        post_order(root->middle);
        post_order(root->right);
        if (root->stat == ONE_ELEMENT) printf("[%d, -] ", root->first);
        else if (root->stat == TWO_ELEMENT) printf("[%d, %d] ", root->first, root->second);
    }
}
