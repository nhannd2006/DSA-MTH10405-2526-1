#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int head, tail;
    int arr[MAX];
} CircQueue;

void initQueue(CircQueue *q) {
    q->head = q->tail = -1;
}

int isEmpty(CircQueue *q) {
    return q->head == -1;
}

int isFull(CircQueue *q) {
    return (q->tail + 1) % MAX == q->head;
}

void put(CircQueue *q, int id) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->head == -1) q->head = 0;
    q->tail = (q->tail + 1) % MAX;
    q->arr[q->tail] = id;
}

int get(CircQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int value = q->arr[q->head];
    if (q->head == q->tail) q->head = q->tail = -1;
    else q->head = (q->head + 1) % MAX;
    return value;
}

void cancelRegistration(CircQueue *q, int id) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return;
    }
    int found = -1;
    int i = q->head;
    do {
        if (q->arr[i] == id) {
            found = i;
            break;
        }
        i = (i + 1) % MAX;
    } while (i != (q->tail + 1) % MAX);
    if (found == -1) {
        printf("ID %d not found.\n", id);
        return;
    }
    if (q->head == q->tail) {
        q->head = q->tail = -1;
        printf(">> Cancellation successful for ID: %d\n", id);
        return;
    }
    do {
        int next = (i + 1) % MAX;
        q->arr[i] = q->arr[next];
        i = next;
    } while (i != q-> tail);
    if (q->tail == 0) q->tail = MAX - 1;
    else q->tail--;
    printf(">> Cancellation successful for ID: %d\n", id);
}

void displayQueue(CircQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return;
    }
    printf("Current queue:\n");
    int i = q->head;
    do {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    } while (i != (q->tail + 1) % MAX);
    printf("\n");
}

void menu(CircQueue *q) {
    int id;
    int choice = -1;
    do {
        system("cls");
        printf("---REGISTRATION QUEUE MANAGEMENT---\n");
        printf("1. Register - Put\n");
        printf("2. Process Next - Get\n");
        printf("3. Cancel Registration\n");
        printf("4. Display Queue\n");
        printf("0. Exit\n--------------------\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                printf("Enter ID to register: ");
                scanf("%d", &id);
                put(q, id);
                printf(">> Registration successful for ID: %d\n", id);
                system("pause");
                break;
            case 2:
                id = get(q);
                if (id != -1) printf(">> Processed the earliest registered ID: %d\n", id);
                system("pause");
                break;
            case 3:
                printf("Enter ID to cancel: ");
                scanf("%d", &id);
                cancelRegistration(q, id);
                system("pause");
                break;
            case 4:
                displayQueue(q);
                system("pause");
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 0);
}

int main() {
    CircQueue q;
    initQueue(&q);
    menu(&q);
    return 0;
}

/*
** OUTPUT 1: thêm vào hàng đợi id 123
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 1
Enter ID to register: 123
>> Registration successful for ID: 123
Press any key to continue . . . 

****************************************
** OUTPUT 2: thêm vào hàng đợi id 987
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 1
Enter ID to register: 987
>> Registration successful for ID: 987
Press any key to continue . . . 

****************************************
** OUTPUT 3: thêm vào hàng đợi id 357
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 1
Enter ID to register: 357
>> Registration successful for ID: 357
Press any key to continue . . . 

****************************************
** OUTPUT 4: thêm vào hàng đợi id 159
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 1
Enter ID to register: 159
>> Registration successful for ID: 159
Press any key to continue . . . 

****************************************
** OUTPUT 5: lấy thông tin id đăng ký sớm nhất
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 2
>> Processed the earliest registered ID: 123
Press any key to continue . . . 

****************************************
** OUTPUT 6: hiển thị hàng đợi
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 4
Current queue:
987 357 159 
Press any key to continue . . . 

****************************************
** OUTPUT 7: thêm vào hàng đợi id 500
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 1
Enter ID to register: 500
>> Registration successful for ID: 500
Press any key to continue . . . 

****************************************
** OUTPUT 8: hủy đăng ký id 159
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 3
Enter ID to cancel: 159
>> Cancellation successful for ID: 159
Press any key to continue . . . 

****************************************
** OUTPUT 9: hủy đăng kí id 100
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 3
Enter ID to cancel: 100
ID 100 not found.
Press any key to continue . . . 

****************************************
** OUTPUT 10: thoát
---REGISTRATION QUEUE MANAGEMENT---
1. Register - Put
2. Process Next - Get
3. Cancel Registration
4. Display Queue
0. Exit
--------------------
Select a function: 0
Goodbye!
*/