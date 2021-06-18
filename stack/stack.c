#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int size;
    int top;
    int *s;
};

void create(struct Stack *st)
{
    printf("Enter size");
    scanf("%d", &st->size);
    st->top = -1;
    st->s = (int*) malloc(st->size * sizeof(int));
}

void display(struct Stack st) 
{
    int i;
    for (i = st.top; i >= 0; i--)
        printf("%d ", st.s[i]);
    printf("\n");
}

int is_full(struct Stack st) 
{
    return (st.top == st.size -1) ? 1 : 0;
}

int is_empty(struct Stack st)
{
    return (st.top == -1) ? 1 : 0;
}

void push(struct Stack *st, int x)
{
    if (is_full(*st)) {
        printf("Stack overflow\n"); 
    }
    else {
        st->top++;
        st->s[st->top] = x;
    }
}

int pop(struct Stack *st, int *flag)
{
    int x = -1;
    if (is_empty(*st)) {
        printf("Stack underflow\n");
        *flag = 0;
    }
    else {
        x = st->s[st->top];
        st->top--;
        *flag = 1;
    }

    return x;
}

int peek(struct Stack st, int index, int *flag)
{
    int x = -1;

    if (is_empty(st)) {
        printf("Stack underflow\n");
        *flag = 0;
        return x;
    }

    if (index > st.top || index < 0) {
        printf("Invalid range\n");
        *flag = 0;
    }
    else {
        x = st.s[st.top - index + 1 ];
        *flag = 1;
    }
    return x;
}

int main (int argc, char *argv[])
{
    struct Stack st;

    int flag = 0;

    create(&st);

    push(&st, 10);

    push(&st, 20);

    push(&st, 30);

    push(&st, 40);

    display(st);

    push(&st, 50);

    push(&st, 60);

    printf("%d \n", pop(&st, &flag));

    printf("%d \n", pop(&st, &flag));

    printf("%d \n", pop(&st, &flag));

    printf("%d \n", pop(&st, &flag));

    printf("%d \n", pop(&st, &flag));

    printf("%d \n", pop(&st, &flag));

    push(&st, 100);

    push(&st, 200);

    push(&st, 300);

    display(st);

    printf("%d \n", peek(st, 2, &flag));

    return 0;
}
