#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node 
{
    int val;
    struct Node *next;
};

struct Stack
{
    struct Node *head;
    int size;
    int e;
};

static int set_size(int size) 
{
    if (size < 1) {
        printf("Invalid size\n");
        return 0;
    }
    else {
        return size;
    }
}

struct Stack* create_stack(int size) 
{
    if (size < 1) {
        printf("Invalid size\n");
        return NULL;
    }

    struct Stack *stack = (struct Stack *) malloc (sizeof(struct Stack));

    if (stack != NULL) {
        stack->head = NULL;
        stack->e = 0;
        stack->size = size;
        return stack;
    }
    else {
        printf("Failed to allocate memory\n");
        return NULL;
    }
}

struct Node* create_node(int val) 
{
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));

    if (node != NULL) {
        node->val = val;
        node->next = NULL;
        return node;
    }
    else {
        printf("Failed to allocate memory\n");
        return NULL;
    }
}

int is_full(struct Stack s) 
{
    if (s.head != NULL) {
        return (s.e == s.size) ? 1 : 0;
    }

    return 0;
}

int is_empty(struct Stack s)
{
    return (s.head == NULL) ? 1 : 0;
}

void push(struct Stack *s, int val)
{
    if (s != NULL) {
        struct Node *tp = create_node(val);
        if (is_full(*s)) {
            printf("Stack overflow\n"); 
        }
        else {
            tp->next = s->head;
            s->head = tp;
            s->e++;
        }
    }
}

int pop(struct Stack *s, int *flag) {
    *flag = 0;
    if (s != NULL) {
        if (is_empty(*s)) {
            printf("Stack undeflow\n");
            *flag = 0;
            return -1;
        }
        else {
            struct Node *tp = s->head;
            int r = s->head->val;

            s->head = s->head->next;

            free(tp);

            tp = NULL;

            *flag = 1;
            
            s->e--;

            return r;
        }
    }

    return -1;
}

int peek(struct Stack s, int index, int *flag) {
    *flag = 0;

    if (index > s.size - 1 || index < 0) {
        printf("Invalid index\n");
        return -1;
    }

    if (is_empty(s)) {
        printf("Stack underflow\n");
        *flag = 0;
        return -1;
    }
    else {
        struct Node *cur = s.head;
        int i;

        for (i = 0; i < index; i++) cur = cur->next;

        *flag = 1;

        return cur->val;
    }
}

void display(struct Stack s)
{
    struct Node *cur;

    if (s.head != NULL) {
        for (cur = s.head; cur != NULL; cur = cur->next) {
            printf("%d ", cur->val);
        }
        printf("\n");
    }
}

void destroy(struct Stack *s)
{
    struct Node *tp, *next;

    if (s != NULL) {
        tp = s->head;
        while (tp != NULL) {
            next = tp->next;
            free(tp);
            tp = next;
        }
        free(s);
    }
}

int parentheses(char *str, int len) {
    struct Stack *s = create_stack(len);
    int i, flag, r = 0;

    for (i = 0; i < len; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') push(s, str[i]);

        if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (is_empty(*s)) {
                destroy(s);
                return 0;
            }
            else pop(s, &flag);
        }
    }

    if (!is_empty(*s)) {
        r = 0;
    } else {
        r = 1;
    }

    destroy(s);

    return r;
}

int out_stack_pre(int c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 3;
    else if (c == '^')
        return 6;
    else if (c == '(')
        return 7;
    else if (c == ')')
        return 0;

    return 0;
}

int in_stack_pre(int c) 
{
   if (c == '+' || c == '-')
       return 2;
   else if (c == '*' || c == '/')
       return 4;
   else if (c == '^')
       return 5;
   else if (c == '(')
       return 0;
}

int is_operand(int c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        return 0;
    else 
        return 1;
}

int is_bracket(int c)
{
    if (c == '(' || c == '[' || c == '{' || c == ')' || c == ']' || c == '}')
        return 1;
    else 
        return 0;
}

char *infix_to_posfix(char *infix)
{
    int i = 0, j = 0, flag = 0;
    char *posfix;
    char tmp;
    int len = strlen(infix);
    struct Stack *s;

    posfix = (char *)malloc((len + 1) *sizeof(char));

    s = create_stack(len);
    while (infix[i] != '\0')
    {
        if (is_operand(infix[i]))
                posfix[j++] = infix[i++];
        else {
            if (is_empty(*s) || out_stack_pre(infix[i]) > in_stack_pre(peek(*s, 0, &flag)))
                push(s, infix[i++]);
            else {
                tmp = pop(s, &flag);
                if (!is_bracket(tmp))
                    posfix[j++] = tmp; 
                else
                    i++;
           }
        }
    }

    while (!is_empty(*s)) posfix[j++] = pop(s, &flag);
    posfix[j] = '\0';
    destroy(s);

    return posfix;
}

int calc(int c, int a, int b)
{
    switch (c) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}

int evaluation(char *posfix)
{
    int i = 0, flag = 0, r = 0;
    int a, b;
    int len = strlen(posfix);
    struct Stack *s;

    s = create_stack(len);

    while (posfix[i] != '\0')
    {
        if (is_operand(posfix[i]))
            push(s, posfix[i++] - '0');
        else {
           b = pop(s, &flag); 
           a = pop(s, &flag);
           //printf("calc(%c, %d, %d)", posfix[i], a, b);
           push(s, calc(posfix[i], a, b));
           i++;
        }
    }

    r = pop(s, &flag);

    destroy(s);

    return r; 
}

int main (int argc, char *argv[])
{

    char *str = "(a+b)-c*(d+b)";
    char *eq = "(a-b)-c))";
    char *eqq = "{[a + b] * (c - d)}";
    char *eqqq = "{[(a - b)] : c}}}";
    char *i2p = "a+b*c-d/e";
    char *i2pp = "((a+b)-c)*d+e/f";
    char *ii2pp = "((3+5)-2)*4+6/2";
    char *iii2p = "(((2-4)*5+1)*2)";
    char *i22p = "a+b*(c+d)/f+d*e)";
    char *pof;

    printf("result = %d\n", parentheses(str, strlen(str)));
    printf("result = %d\n", parentheses(eq, strlen(eq)));
    printf("result = %d\n", parentheses(eqq, strlen(eqq)));
    printf("result = %d\n", parentheses(eqqq, strlen(eqqq)));

    pof = infix_to_posfix(i2p);

    printf("%s \n", pof);

    printf("%s \n", infix_to_posfix(i2pp));

    printf("%s \n", infix_to_posfix(ii2pp));

    printf("%d \n", evaluation(infix_to_posfix(ii2pp)));

    printf("%s \n", infix_to_posfix(iii2p));

    printf("%d \n", evaluation(infix_to_posfix(iii2p)));

    printf("%s\n", infix_to_posfix(i22p));

    return 0;

}
