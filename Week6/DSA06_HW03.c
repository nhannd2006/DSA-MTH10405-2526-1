#include <stdio.h>
#include <string.h>
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

int peek(Stack *s) {
    if (isEmptyStack(s)) return INT_MIN;
    return s->arr[s->top];
}

int precedence(char oper) {
    if (oper == '+' || oper == '-') return 0;
    else if (oper == '*' || oper == '/') return 1;
    else return -1;
}

void reversePostfix(char *str, char *output) {
    Stack s;
    initStack(&s);
    int len = strlen(str);
    int n = 0;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') output[n++] = c;
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!isEmptyStack(&s) && precedence(peek(&s)) >= precedence(c)) {
                output[n++] = (char)pop(&s);
            }
            push(&s, c);
        }
    }
    while (!isEmptyStack(&s)) {
        output[n++] = (char)pop(&s);
    }
    output[n] = '\0';
}

int calculatePostfix(char *postfix) {
    Stack s;
    initStack(&s);
    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (c >= '0' && c <= '9') push(&s, c - '0');
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int val2 = pop(&s);
            int val1 = pop(&s);
            switch(c) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': push(&s, val1 / val2); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    char str[MAX];
    char output[MAX];

    printf("Enter expression: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    reversePostfix(str, output);
    fputs(output, stdout);
    printf("\n");

    int result = 0;
    printf("Result = %d", calculatePostfix(output));
    return 0;
}