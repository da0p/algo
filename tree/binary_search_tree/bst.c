#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "queue_ll.h"
#include "stack_ll.h"
#include "bst.h"

#define QUEUE_SIZE_INIT     3
#define STACK_SIZE_INIT     3

Tree* new_tree(void) {
    
    Tree *tree = (Tree*) malloc(sizeof(Tree));

    if (tree != NULL) {
        tree->root = NULL;
        tree->height = 0;
        tree->nnodes = 0;
        return tree;
    }
    else {
        printf("Failed to allocate memory for tree\n");
        return NULL;
    }
}

Node *create_node(int val) {

    Node *node = (Node *) malloc(sizeof(Node));

    if (node != NULL) {
        node->data = val;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    else {
        printf("Failed to allocate memory for new node\n");
        return NULL;
    }
}

Node* add_node(Node *root, int lr, int val)
{

    Node *node = create_node(val);
    if (root != NULL) {

        if (lr == 1) {
            root->left = node;
            return node;
        }
        else if (lr == 0) {
            root->right = node;
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


Tree *create_bst(void)
{
    Tree *t = NULL;
    Node *l = NULL;
    Node *r = NULL;
    int continued = 0;
    int val;

    t = new_tree();

    printf("Insert root node for binary search tree: \n");
    scanf("%d", &val);
    l = add_node(l, 1, val);
    t->nnodes++;
    t->root = l;
    printf("Continued? [1] Stop [0]: ");
    scanf("%d", &val);
    if (val == 1)
        continued = 1;
    if (continued) {
        printf("Insert node for binary search tree: \n");
        scanf("%d", &val);
    }
    while (continued) {
        if (l == NULL) {
            if (val < r->data) l = add_node(r, 1, val);
            else if (val > r->data) l = add_node(r, 0, val);
            else printf("Duplicate value, continue to insert a new one or stop\n");
            l = t->root;
            r = NULL;
            printf("Continued? [1] Stop [0]: ");
            scanf("%d", &val);
            if (val != 1)
                continued = 0;
            else {
                printf("Insert node for binary search tree: \n");
                scanf("%d", &val);
            }
        }

        if (val < l->data) {
           r = l;
           l = l->left;
        }
        else if (val > l->data) {
            r = l;
            l = l->right; 
        }
        else {
            r = l;
            l = NULL;
        }
    }

    return t;
}

Tree* create_from_pre_order(int *pre, uint32_t size) 
{
    uint32_t i = 0;
    int flag = 0, pflag = 0;
    Node *t = NULL;
    Node *l = NULL;
    Node *r = NULL;
    Stack *s = NULL;
    
    Tree *tree = new_tree();

    r = add_node(r, 1, pre[i]); 

    tree->root = r;

    s = create_stack(s, size);

    l = r;

    i++;
    while (i < size) {
        if (pre[i] < l->data) {
            push(s, l, 0);
            l = add_node(l, 1, pre[i]);            
            i++;
            tree->nnodes++;
        }
        else {
            if (!is_stack_empty(s)) {
                t = peek(s, 0, &flag);
                if (flag) {
                    if (pre[i] > l->data && pre[i] < t->data) {
                        l = add_node(l, 0, pre[i]);
                        i++;
                        tree->nnodes++;
                    }
                    else
                    {
                        l = pop(s, &flag, &pflag);
                    }
                }
            }
            else {
                l = add_node(l, 0, pre[i]);
                i++;
                tree->nnodes++;
            }
        }
    }

    return tree;
}

Node* search(Node *root, int key) 
{
    Node *l = root;

    while (l != NULL) {
        if (key < l->data) l = l->left;
        else if (key > l->data) l = l->right;
        else return l;
    }

    return NULL;
}

Node* rsearch(Node *root, int key)
{
    if (root != NULL) {
        if (key < root->data) return rsearch(root->left, key);
        else if (key > root->data) return rsearch(root->right, key);
        else return root;
    }
    else return NULL;
}

Node* rinsert(Node *l, int key)
{
    Node *tmp = NULL;
    
    if (l == NULL) {
        tmp = create_node(key);
        return tmp;
    }

    if (key < l->data) l->left = rinsert(l->left, key);
    else if (key > l->data) l->right = rinsert(l->right, key);

    return l;
}

Node* in_order_pre(Node *root)
{
    Node *l = root;
    l = l->left;
    while (l != NULL && l->right != NULL) {
        l = l->right; 
    }

    return l;
}

Node* in_order_suc(Node *root)
{
    Node *l = root;
    l = l->right;
    while (l != NULL && l->left != NULL) {
        l = l->left;
    }

    return l;
}

Node *delete(Node **root, Node *l, int key) 
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

    if (key < l->data) {
        l->left = delete(root, l->left, key);
    }
    else if (key > l->data) {
        l->right = delete(root, l->right, key);
    }
    else {
        if (recursive_height(l->left) < recursive_height(l->right)) {
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

    return l;
}

void pre_order(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order(root->left);
        pre_order(root->right);
    }
}

void pre_order_w_stack(Node *root) {
    int flag = 0, pflag = 0;
    uint32_t s_size = STACK_SIZE_INIT;
    Stack *s = create_stack(NULL, STACK_SIZE_INIT);
    Node *l;

    l = root;
    while (l != NULL || !is_stack_empty(s)) {
        if (l != NULL) {
            printf("%d ", l->data);
            if (is_stack_full(s)){
                s_size += STACK_SIZE_INIT;
                s = create_stack(s, s_size); 
            }
            push(s, l, 0);
            l = l->left;
        }
        else {
            l = pop(s, &flag, &pflag);
            if (flag) {
                l = l->right;
            }
        }
    }
}

void in_order(Node *root) {
    if (root != NULL) {
        in_order(root->left);
        printf("%d ", root->data);
        in_order(root->right);
    }
}

void in_order_w_stack(Node *root) {
    int flag = 0, pflag = 0;
    uint32_t s_size = STACK_SIZE_INIT;
    Stack *s = create_stack(NULL, STACK_SIZE_INIT);
    Node *l;

    l = root;
    while (l != NULL || !is_stack_empty(s)) {
        if (l != NULL) {
            if (is_stack_full(s)){
                s_size += STACK_SIZE_INIT;
                s = create_stack(s, s_size); 
            }
            push(s, l, 0);
            l = l->left;
        }
        else {
            l = pop(s, &flag, &pflag);
            if (flag) {
                printf("%d ", l->data);
                l = l->right;
            }
        }
    }
}

void post_order(Node *root) {
    if (root != NULL) {
        post_order(root->left);
        post_order(root->right);
        printf("%d ", root->data);
    }
}

void post_order_w_stack(Node *root) {
    int flag = 0, pflag = 0;
    uint32_t s_size = STACK_SIZE_INIT;
    Stack *s = create_stack(NULL, STACK_SIZE_INIT);
    Node *l;

    l = root;
    while (l != NULL || !is_stack_empty(s)) {
        if (l != NULL) {
            if (is_stack_full(s)){
                s_size += STACK_SIZE_INIT;
                s = create_stack(s, s_size); 
            }
            push(s, l, 0);
            l = l->left;
        }
        else {
            l = pop(s, &flag, &pflag);
            if (pflag == 0) {
                push(s, l, -1);
                if (flag) {
                    l = l->right;
                }
            }
            else {
                printf("%d ", l->data);
                l = NULL;
            }
        }
    }
}

void level_order(Node *root) 
{
    int flag = 0;
    uint32_t q_size = QUEUE_SIZE_INIT;
    Node *tmp = NULL;
    Queue *q = NULL;

    q = create_queue(NULL, QUEUE_SIZE_INIT);

    if (root != NULL) {
        printf("%d ", root->data);
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
                printf("%d ", tmp->left->data);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->left);
            }
            if (tmp->right != NULL) {
                printf("%d ", tmp->right->data);
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp->right);
            }
        }
    }
}

uint32_t recursive_count_node(Node *root)
{
    uint32_t x, y;

    if (root != NULL) {
        x = recursive_count_node(root->left);
        y = recursive_count_node(root->right);
        
        return x + y + 1;
    }
    return 0;
}

int recursive_sum(Node *root)
{
    int x, y;

    if (root != NULL) {
        x = recursive_sum(root->left);
        y = recursive_sum(root->right);

        return x + y + root->data;
    }
    else
        return 0;
}

uint32_t recursive_height(Node *root)
{
    int x, y;

    if (root != NULL) {
        x = recursive_height(root->left);
        y = recursive_height(root->right);

        if (x > y) return x + 1;
        else return y + 1;
    }

    return 0;
}

void destroy_tree(Node *root)
{
    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}
