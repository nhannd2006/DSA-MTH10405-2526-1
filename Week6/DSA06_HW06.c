#include <stdio.h>
#include <limits.h>

#define MAX 100

// ------------------------------------------------------------

typedef struct {
    int arr[MAX];
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

void displayStack(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty.\n");
        return;
    }
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

// ------------------------------------------------------------

typedef struct {
    int head, tail;
    int arr[MAX];
} CircQueue;

void initQueue(CircQueue *q) {
    q->head = q->tail = -1;
}

int isEmptyQueue(CircQueue *q) {
    return q->head == -1;
}

int isFullQueue(CircQueue *q) {
    return (q->tail + 1) % MAX == q->head;
}

void put(CircQueue *q, int value) {
    if (isFullQueue(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->head == -1) q->head = 0;
    q->tail = (q->tail + 1) % MAX;
    q->arr[q->tail] = value;
}

int get(CircQueue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue Underflow\n");
        return INT_MIN;
    }
    int value = q->arr[q->head];
    if (q->head == q->tail) q->head = q->tail = -1;
    else q->head = (q->head + 1) % MAX;
    return value;
}

int front(CircQueue *q) {
    if (isEmptyQueue(q)) return INT_MIN;
    else return q->arr[q->head];
}

void displayCircQueue(CircQueue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty.\n");
        return;
    }
    int i = q->head;
    do {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    } while (i != (q->tail + 1) % MAX);
    printf("\n");
}

// ------------------------------------------------------------

typedef struct {
    int id;
    int floor;
    int capacity;
    CircQueue request;
} WifiPoint;

// Hàm kiểm tra bảo mật (Chặn truy cập không đúng chức năng)
// Ví dụ: chỉ cho phép ID dương 
int isSecureDevice(int id) {
    return (id >= 0);
}



int main() {

    return 0;
}