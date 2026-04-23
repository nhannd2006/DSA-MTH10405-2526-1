#include <stdio.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int head, tail;
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

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int left, int right) {
    int pivotIdx = right;
    right--;
    while(1) {
        while (arr[left] < arr[pivotIdx]) left++;
        while (arr[right] > arr[pivotIdx] && left < right) right--;
        if (left >= right) {
            break;
        } else {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    swap(&arr[left], &arr[pivotIdx]);
    return left;
}

void quickSort(int arr[], int n, int left, int right) {
    if (left >= right) {
        return;
    }
    else {
        int pivotIdx = partition(arr, left, right);
        quickSort(arr, n, left, pivotIdx - 1);
        quickSort(arr, n, pivotIdx + 1, right);
    }
}

int minIndex(int arr[], int n) {
    int min = arr[0];
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            idx = i;
        }
    }
    return idx;
}

int maxIndex(int arr[], int n) {
    int max = arr[0];
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            idx = i;
        }
    }
    return idx;
}

int crossTheBridge1(CircQueue *q, int time[], int n, int k) {
    quickSort(time, n, 0, n - 1);
    if (n < k) return time[n-1];
    for (int i = n - 1; i >= 0; i--) {
        put(q, time[i]);
    }
    int lane[MAX] = {};
    while (!isEmptyQueue(q)) {
        int curr = get(q);
        lane[minIndex(lane, k)] += curr;
    }
    return lane[maxIndex(lane, k)];
}

int crossTheBridge2(CircQueue *q, int time[], int n, int k) {
    quickSort(time, n, 0, n - 1);
    if (n < k) return time[n-1];
    for (int i = 0; i < k; i++) {
        put(q, time[i]);
    }
    for (int i = k; i < n; i++) {
        int finish = get(q);
        put(q, finish + time[i]);
    }
    int value;
    while (!isEmptyQueue(q)) {
        value = get(q);
    }
    return value;
}

int main() {
    int k, n;
    printf("Enter maximum load capacity of the bridge: k = ");
    scanf("%d", &k);
    printf("Enter number of people crossing the bridge: n = ");
    scanf("%d", &n);
    int time[MAX];
    printf("Enter time it takes each person to cross the bridge:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &time[i]);
    }
    CircQueue q;
    initQueue(&q);
    printf("The minimum time it takes the group to cross the bridge (1): %d\n", crossTheBridge1(&q, time, n, k));
    printf("The minimum time it takes the group to cross the bridge (2): %d\n", crossTheBridge2(&q, time, n, k));
    return 0;
}