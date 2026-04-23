#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

void initList(LinkedList *list) {
    list->head = NULL;
}

Node *makeNode(int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void freeList(LinkedList *list) {
    while (list->head != NULL) {
        Node *curr = list->head;
        list->head = curr->next;
        free(curr);
    }
}

void insertHeadList(LinkedList *list, int value) {
    Node *newNode = makeNode(value);
    newNode->next = list->head;
    list->head = newNode;
}

Node *insertPosNode(Node *node, int value, int pos) {
    if (pos == 1) {
        Node *newNode = makeNode(value);
        newNode->next = node;
        return newNode;
    }
    if (node == NULL) return NULL;
    node->next = insertPosNode(node->next, value, pos - 1);
    return node;
}
void insertPosList(LinkedList *list, int value, int pos) {
    list->head = insertPosNode(list->head, value, pos);
}

Node *deletePosNode(Node *node, int pos) {
    if (node == NULL) return NULL;
    if (pos == 1) {
        Node *temp = node->next;
        free(node);
        return temp;
    }
    node->next = deletePosNode(node->next, pos - 1);
    return node;
}
void deletePosList(LinkedList *list, int pos) {
    list->head = deletePosNode(list->head, pos);
}

void printLinkedList(LinkedList *list) {
    Node *node = list->head;
    while (node) {
        printf("Node address: %p | ", &(node->data));
        printf("data = %d | ", node->data);
        if (node->next != NULL) printf("next node address: %p\n", node->next);
        else printf("next node address: null\n");
        node = node->next;
    }
    printf("\n");
}

int main() {
    LinkedList list;
    initList(&list);
    for (int i = 7; i >= 2; i--) {
        insertHeadList(&list, i);
    }
    int pos = 2, value = 1;
    printf("Linked List:\n");
    printLinkedList(&list);
    printf("Linked List after inserting 1 at position k = 2:\n");
    insertPosList(&list, value, pos);
    printLinkedList(&list);
    printf("Linked List after deleting at position k = 2:\n");
    deletePosList(&list, pos);
    printLinkedList(&list);
    freeList(&list);
    return 0;
}

/*
Linked List:
Node address: 00000000007A9920 | data = 2 | next node address: 00000000007A98E0
Node address: 00000000007A98E0 | data = 3 | next node address: 00000000007A98A0
Node address: 00000000007A98A0 | data = 4 | next node address: 00000000007A9860
Node address: 00000000007A9860 | data = 5 | next node address: 00000000007A9CC0
Node address: 00000000007A9CC0 | data = 6 | next node address: 00000000007A6E10
Node address: 00000000007A6E10 | data = 7 | next node address: null

Linked List after inserting 1 at position k = 2:
Node address: 00000000007A9920 | data = 2 | next node address: 00000000007A9960
Node address: 00000000007A9960 | data = 1 | next node address: 00000000007A98E0
Node address: 00000000007A98E0 | data = 3 | next node address: 00000000007A98A0
Node address: 00000000007A98A0 | data = 4 | next node address: 00000000007A9860
Node address: 00000000007A9860 | data = 5 | next node address: 00000000007A9CC0
Node address: 00000000007A9CC0 | data = 6 | next node address: 00000000007A6E10
Node address: 00000000007A6E10 | data = 7 | next node address: null

Linked List after deleting at position k = 2:
Node address: 00000000007A9920 | data = 2 | next node address: 00000000007A98E0
Node address: 00000000007A98E0 | data = 3 | next node address: 00000000007A98A0
Node address: 00000000007A98A0 | data = 4 | next node address: 00000000007A9860
Node address: 00000000007A9860 | data = 5 | next node address: 00000000007A9CC0
Node address: 00000000007A9CC0 | data = 6 | next node address: 00000000007A6E10
Node address: 00000000007A6E10 | data = 7 | next node address: null
*/

/* insertPosNode:
1. BASE CASE: pos = 1 (vị trí chèn là đầu node) hoặc node = NULL (node rỗng)

2. RESULT OF BASE CASE: 
- Nếu pos = 1: trả về node mới (có dữ liệu là value) trỏ vào phần tử đầu node cũ
Khi đó linked list trở thành: newNode >> head >> ...
- Nếu node = NULL: trả về NULL (không chèn được)

3. BEFORE BASE CASE: pos = 2 hoặc node->next = NULL
- Nếu pos = 2: node->next = insertPosNode(node->next, value, 1):
    + tạo newNode (có dữ liệu là value) trỏ vào node->next
    + trả về newNode
    --> node->next = newNode
    Do đó, linked list trở thành: head >> newNode >> next >> ...
- Nếu node->next = NULL: node->next = insertPosNode(NULL, value, pos - 1):
    + trả về rỗng (không chèn được)
    Do đó, linked list giữ nguyên (không thể chèn vì pos lớn hơn số phần tử)

4. BEFORE BEFORE: pos = 3 hoặc node->next->next = NULL
- Nếu pos = 3: node->next = insertPosNode(node->next, value, 2):
    + (node->next)->next = insertPosNode((node->next)->next, value, 1):
        + tạo newNode (có dữ liệu là value) trỏ vào node->next->next
        + trả về newNode
    --> node->next->next = newNode
    Do đó, linked list trở thành: head >> next >> newNode >> nextnext >> ...
- Nếu node->next->next = NULL: node->next = insertPosNode(node->next, value, pos - 1):
    + (node->next)->next = insertPosNode(NULL, value, pos - 1):
    + trả về rỗng (không chèn được)
    Do đó, linked list giữ nguyên (không thể chèn vì pos lớn hơn số phần tử)
*/

/* deletePosNode:
1. BASE CASE: pos = 1 (vị trí xóa là đầu node) hoặc node = NULL (node rỗng)

2. RESULT OF BASE CASE: 
- Nếu pos = 1: xóa head, trả về node->next
Khi đó, linked list trở thành: next >> nextnext >> ...
- Nếu node = NULL: trả về NULL (không xóa được)

3. BEFORE BASE CASE: pos = 2 hoặc node->next = NULL
- Nếu pos = 2: node->next = deletePosNode(node->next, 1):
    + xóa node->next, trả về node->next->next
    --> node->next = node->next->next
    Do đó, linked list trở thành: head >> nextnext >> ...
- Nếu node->next = NULL: node->next = deletePosNode(NULL, pos - 1):
    + trả về rỗng (không xóa được)
    Do đó, linked list giữ nguyên (không thể xóa vì pos lớn hơn số phần tử)

4. BEFORE BEFORE: pos = 3 hoặc node->next->next = NULL
- Nếu pos = 3: node->next = deletePosNode(node->next, 2):
    + (node->next)->next = deletePosNode((node->next)->next, 1):
        + xóa (node->next)->next, trả về node->next->next->next
    --> node->next->next = node->next->next->next
    Do đó, linked list trở thành: head >> next >> nextnextnext >> ...
- Nếu node->next->next = NULL: node->next = deletePosNode(node->next, pos - 1):
    + (node->next)->next = deletePosNode(NULL, pos - 1):
    + trả về rỗng (không xóa được)
    Do đó, linked list giữ nguyên (không thể xóa vì pos lớn hơn số phần tử)
*/
