#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void initializeStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) printf("Stack is full.\n");
    else stack->arr[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    else return stack->arr[stack->top--];
}

void displayStack(Stack *stack) {
    if (isEmpty(stack)) printf("Stack is empty.\n");
    else printf("%d", stack->arr[stack->top]);
}

int main() {
    Stack stack;
    initializeStack(&stack);
    int num[6] = {1,-2,3,-4,5,-6};
    // push
    printf("MAX = %d\n\n", MAX);
    printf("PUSH\n");
    for (int i = 0; i < 6; i++){
        printf("push %d: \n",num[i]);
        if(!isFull(&stack)){
            push(&stack,num[i]);
            displayStack(&stack);
            printf("\n");
        }
        else
            printf("Stack is full.\n\n");
    }
    // pop
    printf("POP\n");
    int i = 0;
    while (!isEmpty(&stack)) {
        printf("pop %d: %d\n", i, pop(&stack));
        displayStack(&stack);
        i++;
        printf("\n");
    }
    return 0;
}

/*
MAX = 5

PUSH
push 1:
1
push -2:
-2
push 3:
3
push -4:
-4
push 5:
5
push -6:
Stack is full.

POP
pop 0: 5
-4
pop 1: -4
3
pop 2: 3
-2
pop 3: -2
1
pop 4: 1
Stack is empty.

*/