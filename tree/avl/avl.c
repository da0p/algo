#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int val) {

    Node *node = (Node *) malloc(sizeof(Node));

    if (node != NULL) {
        node->data = val;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    else {
        printf("Failed to allocate memory for new node\n");
        return NULL;
    }
}

Node* add_node(Node *l, int lr, int val)
{

    Node *node = create_node(val);
    if (l != NULL) {

        if (lr == 1) {
            l->left = node;
            return node;
        }
        else if (lr == 0) {
            l->right = node;
            return node;
        }
        else {
            free(node);
            return NULL;
        }
    }
    else {
        return node;
    }
}

int node_height(Node *l)
{
    int hl, hr;
    hl = l && l->left ? l->left->height : 0;
    hr = l && l->right ? l->right->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

int balance_factor(Node *l)
{
    int hl, hr;

    hl = l && l->left ? l->left->height : 0;
    hr = l && l->right ? l->right->height : 0;

    printf("bf of %d = %d\n", l->data, hl - hr);

    return hl - hr;
}

Node* in_order_pre(Node *root)
{
    Node *l = root;
    l = l->left;
    while (l != NULL && l->right != NULL)
        l = l->right;

    return l;
}

Node* in_order_suc(Node *root)
{
    Node *l = root;
    l = l->right;
    while (l != NULL && l->left != NULL)
        l = l->left;

    return l;
}

Node* ll_rotate(Node **root, Node *l)
{
    Node *pl = l->left;
    Node *plr = pl->right;

    pl->right = l;
    l->left = plr;
    l->height = node_height(l);
    pl->height = node_height(pl);

    if (*root == l)
        *root = pl;

    return pl;
}

Node* lr_rotate(Node **root, Node *l)
{
    Node *pl = l->left;
    Node *plr = pl->right;

    pl->right = plr->left;
    l->left = plr->right;
    plr->right = l;
    plr->left = pl;

    pl->height = node_height(pl); 
    l->height = node_height(l);
    plr->height = node_height(plr);

    if (*root == l)
        *root = plr;

    return plr;
}
Node* rr_rotate(Node **root, Node *l)
{
    Node *pr = l->right;
    Node *prl = pr->left;

    l->right = prl;
    pr->left = l;
    l->height = node_height(l);
    pr->height = node_height(pr);

    if (*root == l)
        *root = pr;

    return pr;
}

Node* rl_rotate(Node **root, Node *l)
{
    Node *pr = l->right;
    Node *prl = pr->left;

    l->right = prl->left;
    pr->left = prl->right;
    prl->left = l;
    prl->right = pr;

    pr->height = node_height(pr);
    l->height = node_height(l);
    prl->height = node_height(prl);

    if (*root == l)
        *root = prl;

    return prl;
}

Node* rinsert(Node **root, Node *l, int key)
{
    Node *tmp = NULL;
    
    if (l == NULL) {
        printf("Insert %d\n", key);
        tmp = create_node(key);
        return tmp;
    }

    if (key < l->data) l->left = rinsert(root, l->left, key);
    else if (key > l->data) l->right = rinsert(root, l->right, key);

    l->height = node_height(l); 
    printf("height of %d is %d\n", l->data, l->height);

    if (balance_factor(l) == 2 && balance_factor(l->left) == 1)
        return ll_rotate(root, l);
    else if (balance_factor(l) == 2 && balance_factor(l->left) == -1)
        return lr_rotate(root, l);
    else if (balance_factor(l) == -2 && balance_factor(l->right) == -1)
        return rr_rotate(root, l);
    else if (balance_factor(l) == -2 && balance_factor(l->right) == 1)
        return rl_rotate(root, l);

    return l;
}

Node* delete(Node **root, Node *l, int key)
{
    Node *q = NULL;

    if (l == NULL)
        return NULL;

    if (l->left == NULL && l->right == NULL)
    {
        if (l == *root)
            *root = NULL;
        free(l);
        return NULL;
    }

    if (key < l->data) l->left = delete(root, l->left, key);
    else if (key > l->data) l->right = delete(root, l->right, key);
    else {
       if (node_height(l->left) < node_height(l->right)) {
           q = in_order_pre(l);
           l->data = q->data;
           l->left = delete(root, l->left, q->data);
       }
       else {
           q = in_order_suc(l);
           l->data = q->data;
           l->right = delete(root, l->right, q->data);
       }
    }

       /* Update height */
       l->height = node_height(l);

       /* balance factor and rotation */
       if (balance_factor(l) == 2 && balance_factor(l->left) == 1) // L1
           return ll_rotate(root, l);
       else if (balance_factor(l) == 2 && balance_factor(l->left) == -1)
           return lr_rotate(root, l);
       else if (balance_factor(l) == -2 && balance_factor(l->right) == -1)
           return rr_rotate(root, l);
       else if (balance_factor(l) == -2 && balance_factor(l->right) == 1)
           return rl_rotate(root, l);
       else if (balance_factor(l) == 2 && balance_factor(l->left) == 0)
           return ll_rotate(root, l);
       else if (balance_factor(l) == -2 && balance_factor(l->right) == 0)
           return rr_rotate(root, l);
       
    return l;
}

void pre_order(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order(root->left);
        pre_order(root->right);
    }
}


void in_order(Node *root) {
    if (root != NULL) {
        in_order(root->left);
        printf("%d ", root->data);
        in_order(root->right);
    }
}

void post_order(Node *root) {
    if (root != NULL) {
        post_order(root->left);
        post_order(root->right);
        printf("%d ", root->data);
    }
}

void destroy_tree(Node *root)
{
    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}

int main(int argc, char *argv[])
{

    Node *root = NULL;
    
    root = rinsert(&root, root, 10);
    rinsert(&root, root, 5);
    rinsert(&root, root, 6);
    rinsert(&root, root, 4);
    if (root != NULL)
        pre_order(root);
    printf("\n");

    delete(&root, root, 10);

    if (root != NULL)
        pre_order(root);

    printf("\n");
}
