#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *makeNode(int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

//========================================

typedef struct {
    Node *top;
} Stack;

void initStack(Stack *stack) {
    stack->top = NULL;
}

int isEmptyStack(Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, int value) {
    Node *newNode = makeNode(value);
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if(isEmptyStack(stack)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    }
    Node *temp = stack->top;
    stack->top = temp->next;
    int value = temp->data;
    free(temp);
    return value;
}

int peek(Stack *stack) {
    if (isEmptyStack(stack)) return INT_MIN;
    return stack->top->data;
}

void displayStack(Stack *stack) {
    if (isEmptyStack(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    Node *curr = stack->top;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void freeStack(Stack *stack) {
    while (!isEmptyStack(stack)) {
        pop(stack);
    }
}

//========================================

typedef struct {
    Node *head, *tail;
} Queue;

void initQueue(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

int isEmptyQueue(Queue *queue) {
    return queue->head == NULL;
}

void put(Queue *queue, int value) {
    Node *newNode = makeNode(value);
    if (isEmptyQueue(queue)) queue->head = queue->tail = newNode;
    else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

int get(Queue *queue) {
    if (isEmptyQueue(queue)) return INT_MIN;
    Node *temp = queue->head;
    queue->head = temp->next;
    int value = temp->data;
    if (queue->head == NULL) queue->tail = NULL;
    free(temp);
    return value;
}

int front(Queue *queue) {
    if (isEmptyQueue(queue)) return INT_MIN;
    return queue->head->data;
}

void displayQueue(Queue *queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    Node *curr = queue->head;
    while (curr != queue->tail) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("%d ", curr->data);
    printf("\n");
}

void freeQueue(Queue *queue) {
    while (!isEmptyQueue(queue)) {
        get(queue);
    }
}

//========================================


int main() {
    Stack stack;
    initStack(&stack);
    printf("Stack: ");
    displayStack(&stack);
    push(&stack, 1);
    printf("push 1: ");
    displayStack(&stack);
    push(&stack, 6);
    printf("push 6: ");
    displayStack(&stack);
    pop(&stack);
    printf("pop: ");
    displayStack(&stack);
    freeStack(&stack);

    Queue queue;
    initQueue(&queue);
    printf("Queue: ");
    displayQueue(&queue);
    put(&queue, 1);
    printf("put 1: ");
    displayQueue(&queue);
    put(&queue, 6);
    printf("put 6: ");
    displayQueue(&queue);
    get(&queue);
    printf("get: ");
    displayQueue(&queue);
    freeQueue(&queue);

    return 0;
}

/*
Stack: Stack is empty.
push 1: 1
push 6: 6 1
pop: 1
Queue: Queue is empty.
put 1: 1
put 6: 1 6
get: 6
*/