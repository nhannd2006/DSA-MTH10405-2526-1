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

Node *makeNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertHeadList(LinkedList *list, int data) {
    Node *newNode = makeNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

void insertTailList(LinkedList *list, int value) {
    Node *newNode = makeNode(value);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node *temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteHeadList(LinkedList *list) {
    if (list->head) {
        Node *temp = list->head;
        list->head = temp->next;
        free(temp);
    }
}

void deleteTailList(LinkedList *list) {
    if (list->head == NULL) return;
    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
        return;
    }
    Node *temp = list->head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void freeLinkedList(LinkedList *list) {
    while (list->head != NULL) {
        Node *temp = list->head;
        list->head = temp->next;
        free(temp);
    }
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
    int arr[8] = {2, 12, 9, 0, 11, 3, 4, 8};
    for (int i = 0; i < 8; i++) {
        insertTailList(&list, arr[i]);
    }
    printf("Linked List:\n");
    printLinkedList(&list);
    insertHeadList(&list, 19);
    printf("Linked List after inserting 19 at head:\n");
    printLinkedList(&list);
    insertTailList(&list, -3);
    printf("Linked List after inserting -3 at tail:\n");
    printLinkedList(&list);
    deleteHeadList(&list);
    printf("Linked List after deleting at head:\n");
    printLinkedList(&list);
    deleteTailList(&list);
    printf("Linked List after deleting at tail:\n");
    printLinkedList(&list);
    freeLinkedList(&list);
    return 0;
}

/*
Linked List:
Node address: 0000000000776FA0 | data = 2 | next node address: 0000000000779E50
Node address: 0000000000779E50 | data = 12 | next node address: 000000000077F5F0
Node address: 000000000077F5F0 | data = 9 | next node address: 000000000077F630
Node address: 000000000077F630 | data = 0 | next node address: 000000000077F670
Node address: 000000000077F670 | data = 11 | next node address: 000000000077F6B0
Node address: 000000000077F6B0 | data = 3 | next node address: 000000000077F6F0
Node address: 000000000077F6F0 | data = 4 | next node address: 000000000077F730
Node address: 000000000077F730 | data = 8 | next node address: null

Linked List after inserting 19 at head:
Node address: 00000000007807A0 | data = 19 | next node address: 0000000000776FA0
Node address: 0000000000776FA0 | data = 2 | next node address: 0000000000779E50
Node address: 0000000000779E50 | data = 12 | next node address: 000000000077F5F0
Node address: 000000000077F5F0 | data = 9 | next node address: 000000000077F630
Node address: 000000000077F630 | data = 0 | next node address: 000000000077F670
Node address: 000000000077F670 | data = 11 | next node address: 000000000077F6B0
Node address: 000000000077F6B0 | data = 3 | next node address: 000000000077F6F0
Node address: 000000000077F6F0 | data = 4 | next node address: 000000000077F730
Node address: 000000000077F730 | data = 8 | next node address: null

Linked List after inserting -3 at tail:
Node address: 00000000007807A0 | data = 19 | next node address: 0000000000776FA0
Node address: 0000000000776FA0 | data = 2 | next node address: 0000000000779E50
Node address: 0000000000779E50 | data = 12 | next node address: 000000000077F5F0
Node address: 000000000077F5F0 | data = 9 | next node address: 000000000077F630
Node address: 000000000077F630 | data = 0 | next node address: 000000000077F670
Node address: 000000000077F670 | data = 11 | next node address: 000000000077F6B0
Node address: 000000000077F6B0 | data = 3 | next node address: 000000000077F6F0
Node address: 000000000077F6F0 | data = 4 | next node address: 000000000077F730
Node address: 000000000077F730 | data = 8 | next node address: 00000000007807E0
Node address: 00000000007807E0 | data = -3 | next node address: null

Linked List after deleting at head:
Node address: 0000000000776FA0 | data = 2 | next node address: 0000000000779E50
Node address: 0000000000779E50 | data = 12 | next node address: 000000000077F5F0
Node address: 000000000077F5F0 | data = 9 | next node address: 000000000077F630
Node address: 000000000077F630 | data = 0 | next node address: 000000000077F670
Node address: 000000000077F670 | data = 11 | next node address: 000000000077F6B0
Node address: 000000000077F6B0 | data = 3 | next node address: 000000000077F6F0
Node address: 000000000077F6F0 | data = 4 | next node address: 000000000077F730
Node address: 000000000077F730 | data = 8 | next node address: 00000000007807E0
Node address: 00000000007807E0 | data = -3 | next node address: null

Linked List after deleting at tail:
Node address: 0000000000776FA0 | data = 2 | next node address: 0000000000779E50
Node address: 0000000000779E50 | data = 12 | next node address: 000000000077F5F0
Node address: 000000000077F5F0 | data = 9 | next node address: 000000000077F630
Node address: 000000000077F630 | data = 0 | next node address: 000000000077F670
Node address: 000000000077F670 | data = 11 | next node address: 000000000077F6B0
Node address: 000000000077F6B0 | data = 3 | next node address: 000000000077F6F0
Node address: 000000000077F6F0 | data = 4 | next node address: 000000000077F730
Node address: 000000000077F730 | data = 8 | next node address: null
*/