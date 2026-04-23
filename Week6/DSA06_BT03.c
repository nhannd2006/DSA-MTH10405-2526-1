#include <stdio.h>

#define CAP 7

typedef struct {
    int head, tail;
    int arr[CAP];
} CircQueue;

void initQueue(CircQueue *queue) {
    queue->head = queue->tail = -1;
}

int isEmpty(CircQueue *queue) {
    return queue->head == -1;
}

int isFull(CircQueue *queue) {
    return (queue->tail + 1) % CAP == queue->head;
}

void put(CircQueue *queue, int value) {
    if (isFull(queue)) {
        printf("Queue Overflow\n");
        return;
    }
    if (queue->head == -1) queue->head = 0;
    queue->tail = (queue->tail + 1) % CAP;
    queue->arr[queue->tail] = value;
}

int get(CircQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = queue->arr[queue->head];
    if (queue->head == queue->tail) queue->head = queue->tail = -1;
    else queue->head = (queue->head + 1) % CAP;
    return value;
}

void displayCircQueue(CircQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    int i = queue->head;
    do {
        printf("%d ", queue->arr[i]);
        i = (i + 1) % CAP;
    } while (i != (queue->tail + 1) % CAP);
    printf("\n");
}

int main() {
    CircQueue q;
    initQueue(&q);
    printf("MAX = %d\n", CAP);
    int num[CAP] = {-5, 2, 4, -3, 1, 0, 9};
    int num2[3] = {8, 4, -3};
    for (int i = 0; i < CAP; i++) {
        printf("put %d: ", num[i]);
        put(&q, num[i]);
        displayCircQueue(&q);
    }
    for (int i = 0; i < 5; i++) {
        printf("get %d: ", get(&q));
        displayCircQueue(&q);
    }
    for (int i = 0; i < 3; i++) {
        printf("put %d: ", num2[i]);
        put(&q, num2[i]);
        displayCircQueue(&q);
    }
    for (int i = 0; i < 3; i++) {
        printf("get %d: ", get(&q));
        displayCircQueue(&q);
    }
    return 0;
}

/*
MAX = 7
put -5: -5 
put 2: -5 2
put 4: -5 2 4
put -3: -5 2 4 -3
put 1: -5 2 4 -3 1
put 0: -5 2 4 -3 1 0
put 9: -5 2 4 -3 1 0 9
get -5: 2 4 -3 1 0 9
get 2: 4 -3 1 0 9
get 4: -3 1 0 9
get -3: 1 0 9
get 1: 0 9
put 8: 0 9 8
put 4: 0 9 8 4
put -3: 0 9 8 4 -3
get 0: 9 8 4 -3
get 9: 8 4 -3
get 8: 4 -3
*/