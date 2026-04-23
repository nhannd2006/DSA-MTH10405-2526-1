#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    char arr[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

int isFullStack(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFullStack(s)) printf("Stack is full.\n");
    else s->arr[++s->top] = value;
}

int pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    }
    else return s->arr[s->top--];
}

int main() {
    Stack stack;
    initStack(&stack);
    char ch;
    while (scanf("%c", &ch) != EOF) {
        push(&stack, ch);
    }
    while (!isEmptyStack(&stack)) {
        printf("%c", pop(&stack));
    }
    return 0;
}