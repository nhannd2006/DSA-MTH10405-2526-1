#include <stdio.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

typedef struct {
    int arr[MAX];
    int head, tail;
} CircQueue;

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

void recursivePopStack(Stack *s) {
    if (isEmptyStack(s)) return;
    s->top --;
    displayStack(s);
    recursivePopStack(s);
}

void initQueue(CircQueue *q) {
    q->head = q->tail = -1;
}

int isEmptyQueue(CircQueue *q) {
    return q->head == -1;
}

int isFullQueue(CircQueue *q) {
    return q->head == (q->tail + 1) % MAX;
}

void put(CircQueue *q, int value) {
    if (isFullQueue(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmptyQueue(q)) q->head = 0;
    q->tail = (q->tail + 1) % MAX;
    q->arr[q->tail] = value;
}

void displayQueue(CircQueue *q) {
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

void recursiveGetQueue(CircQueue *q) {
    if (isEmptyQueue(q)) return;
    if (q->head == q->tail) q->head = q->tail = -1;
    else q->head = (q->head + 1) % MAX;
    displayQueue(q);
    recursiveGetQueue(q);
}

int linearSearch(int arr[], int n, int value) {
    if (n == 0) return -1;
    if (arr[n - 1] == value) return n - 1;
    return linearSearch(arr, n - 1, value);
}

int binarySearch(int arr[], int n, int value, int left, int right) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (value == arr[mid]) return mid;
    if (value < arr[mid]) {
        return binarySearch(arr, n, value, left, mid - 1);
    } else {
        return binarySearch(arr, n, value, mid + 1, right);
    }
}

int main() {
    int n = 9;
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    Stack s;
    initStack(&s);
    CircQueue q;
    initQueue(&q);
    for (int i = 0; i < n; i++) {
        push(&s, arr[i]);
        put(&q, arr[i]);
    }
    displayStack(&s);
    recursivePopStack(&s);
    displayQueue(&q);
    recursiveGetQueue(&q);
    int value = 5;
    int idx = binarySearch(arr, n, value, 0, n - 1);
    if (idx == -1) printf("\nNot found %d in array\n", value);
    else printf("\nFound %d at %d", value, idx);
    return 0;
}

/*
1 3 5 7 9 11 13 15 17 
1 3 5 7 9 11 13 15 
1 3 5 7 9 11 13 
1 3 5 7 9 11 
1 3 5 7 9 
1 3 5 7 
1 3 5 
1 3
1
Stack is empty.
1 3 5 7 9 11 13 15 17
3 5 7 9 11 13 15 17 
5 7 9 11 13 15 17
7 9 11 13 15 17
9 11 13 15 17
11 13 15 17
13 15 17
15 17
17
Queue is empty.

Found 5 at 2
*/

/* POP - STACK:
1. BASE CASE: isEmptyStack(s) hay s->top = -1
2. RESULT OF BASE CASE: return
3. BEFORE BASE CASE: s->top = 0 (stack có 1 ngăn - đỉnh stack là 0)
    s->top-- : s->top = -1 (BASE CASE) 
        return
4. BEFORE BEFORE: s->top = 1 (stack có 2 ngăn - đỉnh stack là 1)
    s->top-- : s->top = 0 (BEFORE BASE CASE)
        s->top-- : s->top = -1 (BASE CASE) 
            return
*/

/* GET - QUEUE:
1. BASE CASE: isEmptyQueue(q) hay q->head = -1
2. RESULT OF BASE CASE: return
3. BEFORE BASE CASE: q->head = q->tail
    vì q->head = q->tail nên q->head = q->tail = -1
    recursiveGetQueue(q)
        vì q->head = -1 --> return
4. BEFORE BEFORE: q->head + 1 = q->tail
    vì q->head != q->tail nên q->head = (q->head + 1) % MAX = q->tail (để đơn giản nên ta giả sử q->head không nằm ở cuối mảng q->arr)
    recursiveGetQueue(q)
        vì q->head == q->tail nên q->head = q->tail = -1
        recursiveGetQueue(q)
            vì q->head = -1 --> return
*/

/* linearSearch:
1. BASE CASE: n = 0 (mảng rỗng) hoặc arr[n - 1] = value (tại vị trí đang xét là giá trị cần tìm)
2. RESULT OF BASE CASE:
n = 0: 
    --> -1 (mảng rỗng nên trả về -1, tức không tìm thấy trong mảng)
arr[n - 1] = value:
    linearSearch(arr, n) --> n - 1 (trả về vị trí tìm thấy)
3. BEFORE BASE CASE: (n = 1) hoặc (n > 1 và arr[n - 2] = value)
Nếu n = 1: linearSearch(arr, 1) 
    - nếu arr[0] = value (BASE CASE) --> 0
    - ngược lại: linearSearch(arr, 0) (BASE CASE) --> -1
Nếu n > 1 và arr[n - 2] = value: linearSearch(arr, n) 
    - nếu arr[n - 1] = value (BASE CASE) --> n - 1
    - ngược lại: linearSearch(arr, n - 1) 
        vì arr[n - 2] = value --> n - 2
4. BEFORE BEFORE: (n = 2) hoặc (n > 2 và arr[n - 3] = value)
Nếu n = 2 và arr[n - 1] != value và arr[n - 2] != value: linearSearch(arr, 2)
    - nếu arr[1] = value (BASE CASE) --> 1
    - ngược lại: linearSearch(arr, 1) (BEFORE BASE CASE)
        + nếu arr[0] = value (BASE CASE) --> 0
        + ngược lại: linearSearch(arr, 0) (BASE CASE) --> -1
Nếu n > 2 và arr[n - 3] = value:
    - nếu arr[n - 1] = value (BASE CASE) --> n - 1
    - ngược lại: linearSearch(arr, n - 1) (BEFORE BASE CASE)
        + nếu arr[n - 2] = value (BASE CASE) --> n - 2
        + ngược lại: linearSearch(arr, n - 2) 
            do arr[n - 3] = value --> n - 3
*/

/* binarySearch
1. BASE CASE: left > right --> tức mảng có 0 phần tử
2. RESULT OF BASE CASE: -1 --> tức value không được tìm thấy 
3. BEFORE BASE CASE: left = right
    - Khi đó: mid = left
    - Nếu arr[mid] = value thì trả về mid 
        --> tức value được tìm thấy ở mid
    - Ngược lại, tiếp tục tìm kiếm 1 trong 2 mảng con [left, mid - 1] và [mid + 1, right],
    tức là [left, left - 1] và [left + 1, left]
        --> khi đó 2 mảng con đều rơi vào base case
4. BEFORE BEFORE: left + 1 = right
    - Khi đó: mid = left
    - Nếu arr[mid] = value thì trả về mid
        --> tức value được tìm thấy ở mid
    - Ngược lại, tiếp tục tìm kiếm 1 trong 2 mảng con [left, mid - 1] và [mid + 1, right], 
    tức là [left, left - 1] và [left + 1, left + 1]
        --> khi đó 2 mảng con hoặc rơi vào base case hoặc rơi vào before base case
*/
