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

void insertPosList(LinkedList *list, int value, int pos) {
    if (pos < 1) return;
    if (pos == 1) {
        insertHeadList(list, value);
        return;
    }
    Node *curr = list->head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }
    if (curr == NULL) return;
    Node *newNode = makeNode(value);
    newNode->next = curr->next;
    curr->next = newNode;
}

void deleteHeadList(LinkedList *list) {
    if (list->head == NULL) return;
    Node *temp = list->head;
    list->head = temp->next;
    free(temp);
}

void deletePosList(LinkedList *list, int pos) {
    if (pos < 1) return;
    if (pos == 1) {
        deleteHeadList(list);
        return;
    }
    Node *curr = list->head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++) {
        curr = curr->next;
    }
    if (curr == NULL || curr->next == NULL) return;
    Node *temp = curr->next;
    curr->next = temp->next;
    free(temp);
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
Node address: 000000000066F6B0 | data = 2 | next node address: 000000000066F670
Node address: 000000000066F670 | data = 3 | next node address: 000000000066F630
Node address: 000000000066F630 | data = 4 | next node address: 000000000066F5F0
Node address: 000000000066F5F0 | data = 5 | next node address: 0000000000669E50
Node address: 0000000000669E50 | data = 6 | next node address: 0000000000666FA0
Node address: 0000000000666FA0 | data = 7 | next node address: null

Linked List after inserting 1 at position k = 2:
Node address: 000000000066F6B0 | data = 2 | next node address: 0000000000670720
Node address: 0000000000670720 | data = 1 | next node address: 000000000066F670
Node address: 000000000066F670 | data = 3 | next node address: 000000000066F630
Node address: 000000000066F630 | data = 4 | next node address: 000000000066F5F0
Node address: 000000000066F5F0 | data = 5 | next node address: 0000000000669E50
Node address: 0000000000669E50 | data = 6 | next node address: 0000000000666FA0
Node address: 0000000000666FA0 | data = 7 | next node address: null

Linked List after deleting at position k = 2:
Node address: 000000000066F6B0 | data = 2 | next node address: 000000000066F670
Node address: 000000000066F670 | data = 3 | next node address: 000000000066F630
Node address: 000000000066F630 | data = 4 | next node address: 000000000066F5F0
Node address: 000000000066F5F0 | data = 5 | next node address: 0000000000669E50
Node address: 0000000000669E50 | data = 6 | next node address: 0000000000666FA0
Node address: 0000000000666FA0 | data = 7 | next node address: null
*/