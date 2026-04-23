#include <stdio.h>
#include <stdlib.h>
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

int parenthesis(char *str, Stack *stack, char errorIdx[], int *n) {
    int valid = 1;
    int errorCount = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char current = str[i];
        if (current == '(' || current == '[' || current == '{') push(stack, current);
        else if (current == ')' || current == ']' || current == '}') {
            char top = peek(stack);
            if (!((top == '(' && current == ')') || (top == '[' && current == ']') || (top == '{' && current == '}'))) {
                valid = 0;
                errorIdx[errorCount++] = i;
                switch (top) {
                    case '(':
                        str[i] = ')';
                        break;
                    case '[':
                        str[i] = ']';
                        break;
                    case '{':
                        str[i] = '}';
                        break;
                }
            }
            pop(stack);
        }
    }
    *n = errorCount;
    return valid;
}

int main() {
    Stack stack;
    initStack(&stack);
    char str[MAX];
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    char errorIdx[MAX/2];
    int n;
    if (parenthesis(str, &stack, errorIdx, &n)) {
        printf("No error.\n");
    } else {
        printf("Error at");
        for (int i = 0; i < n; i++) {
            printf(" %d", errorIdx[i]);
        }
        printf("\n");
        fputs(str, stdout);
    }
    return 0;
}