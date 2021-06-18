#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "queue_ll.h"
#include "stack_ll.h"
#include "binary_tree.h"

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

Tree* create_tree(void) {
    
    int val, lr;
    int flag = 0;
    uint32_t q_size = QUEUE_SIZE_INIT;
    Node *root = NULL;
    Node *tmp = NULL;
    Queue *q = NULL;
    Tree *t = NULL;

    t = new_tree();

    q = create_queue(NULL, q_size);

    printf("Enter root node: \n");
    scanf("%d", &val);
    
    root = add_node(root, 1, val);
    t->nnodes++;

    if (root != NULL) {
        enqueue(q, root);
        t->root = root;
    }
    else {
        printf("root node is NULL\n");
        return NULL;
    }

    lr = 1;
    while (!is_queue_empty(q)) {
        root = dequeue(q, &flag);
        printf("1: only left node of %d\n", root->data);
        printf("0: only right node of %d\n", root->data);
        printf("2: both nodes of %d\n", root->data);
        printf("-1: no child nodes of %d\n", root->data);
        scanf("%d", &lr);
        if (lr == 1) {
            printf("Insert left child node of %d\n", root->data);
            scanf("%d", &val);
            tmp = add_node(root, 1, val);
            if (tmp != NULL){
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp);
                t->nnodes++;
            }
        }
        else if (lr == 0)
        {
            printf("Insert right child node of %d\n", root->data);
            scanf("%d", &val);
            tmp = add_node(root, 0, val);
            if (tmp != NULL){
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                }
                enqueue(q, tmp);
                t->nnodes++;
            }
        }
        else if (lr == 2)
        {
            printf("Insert left child node of %d\n", root->data);
            scanf("%d", &val);
            tmp = add_node(root, 1, val);
            if (tmp != NULL){
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                } 
                enqueue(q, tmp);
                t->nnodes++;
            }
            printf("Insert right child node of %d\n", root->data);
            scanf("%d", &val);
            tmp = add_node(root, 0, val);
            if (tmp != NULL) {
                if (is_queue_full(q)) {
                    q_size += QUEUE_SIZE_INIT;
                    q = create_queue(q, q_size);
                } 
                enqueue(q, tmp);
                t->nnodes++;
            } 
        }
    }

    destroy_queue(q);

    return t;
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
