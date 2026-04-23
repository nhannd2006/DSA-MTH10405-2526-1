#include <stdio.h>

#define MAX 5

typedef struct {
    int head, tail;
    int arr[MAX];
} Queue;

void initializeQueue(Queue *queue) {
    queue->head = 0;
    queue->tail = -1;
}

int isFull(Queue *queue) {
    return (queue->head == 0 && queue->tail == MAX - 1);
}

int isEmpty(Queue *queue) {
    return queue->head > queue->tail;
}

void put(Queue *queue, int value) {
    queue->arr[++queue->tail] = value;
}

int get(Queue *queue) {
    return queue->arr[queue->head++];
}

void displayQueue(Queue *queue) {
    if (isEmpty(queue)) printf("Queue is empty.\n");
    else {
        for (int i = queue->head; i <= queue->tail; i++) {
            printf("%d ", queue->arr[i]);
        }
    }
}

int main() {
    Queue q;
    initializeQueue(&q);
    int num[6] = {1,-2,3,-4,5,-6};
    // put
    printf("MAX = %d\n\n", MAX);
    printf("PUT\n");
    for (int i = 0; i < 6; i++){
        printf("put %d: \n",num[i]);
        if(!isFull(&q)){
            put(&q,num[i]);
            displayQueue(&q);
            printf("\n");
        }
        else
            printf("Queue is full. \n\n");
    }
    // get
    printf("GET\n");
    int i = 0;
    while (!isEmpty(&q)) {
        printf("get %d: %d\n",i, get(&q));
        displayQueue(&q);
        i++;
        printf("\n");
    }
    return 0;
}

/*
MAX = 5

PUT
put 1:
1
put -2:
1 -2
put 3:
1 -2 3
put -4:
1 -2 3 -4
put 5:
1 -2 3 -4 5
put -6:
Queue is full.

GET
get 0: 1
-2 3 -4 5
get 1: -2
3 -4 5
get 2: 3
-4 5
get 3: -4
5
get 4: 5
Queue is empty.

*/