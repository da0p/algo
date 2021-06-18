#include <stdio.h>
#include <stdlib.h>

typedef struct TTNode
{
    int first;
    int second;

    struct TTNode *left;
    struct TTNode *middle;
    struct TTNode *right;

    int stat;
} TTNode;

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
    else return NULL;
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
}

void display(TTNode *root) {
    if (root != NULL) {
        if (root->stat == 1) {
            printf("[%d, -] ", root->first);
        }
        else if (root->stat == 2) {
            printf("[%d, %d] ", root->first, root->second);
        }
        display(root->left);
        display(root->middle);
        display(root->right);
    }
}

int main(int argc, char *argv[])
{
    TTNode *root = NULL;

    root = insert(root, root, 20);

    insert(root, root, 30);

    insert(root, root, 40);

    insert(root, root, 50);

    insert(root, root, 60);

    insert(root, root, 10);

    insert(root, root, 15);

    insert(root, root, 70);

    insert(root, root, 80);

    display(root);

    printf("\n");

    return 0;
}
