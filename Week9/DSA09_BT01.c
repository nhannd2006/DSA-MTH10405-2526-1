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
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

void insertHeadList(LinkedList *list, int value) {
    Node *newNode = makeNode(value);
    newNode->next = list->head;
    list->head = newNode;
}

void deleteHeadList(LinkedList *list) {
    if (list->head == NULL) return;
    Node *temp = list->head;
    list->head = temp->next;
    free(temp);
}

void printList(LinkedList *list) {
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

void freeList(LinkedList *list) {
    while (list->head != NULL) {
        Node *curr = list->head;
        list->head = curr->next;
        free(curr);
    }
}

int main() {
    LinkedList list;
    initList(&list);
    for (int i = 0; i < 10; i ++) {
        insertHeadList(&list, i);
    }
    printf("Linked List:\n");
    printList(&list);
    insertHeadList(&list, 15);
    printf("Linked List after inserting 15 at head:\n");
    printList(&list);
    deleteHeadList(&list);
    printf("Linked List after deleting at head:\n");
    printList(&list);
    freeList(&list);
    return 0;
}

/*
Linked List:
Node address: 000000000010F7B0 | data = 9 | next node address: 000000000010F770
Node address: 000000000010F770 | data = 8 | next node address: 000000000010F730
Node address: 000000000010F730 | data = 7 | next node address: 000000000010F6F0
Node address: 000000000010F6F0 | data = 6 | next node address: 000000000010F6B0
Node address: 000000000010F6B0 | data = 5 | next node address: 000000000010F670
Node address: 000000000010F670 | data = 4 | next node address: 000000000010F630
Node address: 000000000010F630 | data = 3 | next node address: 000000000010F5F0
Node address: 000000000010F5F0 | data = 2 | next node address: 0000000000109E50
Node address: 0000000000109E50 | data = 1 | next node address: 0000000000106FA0
Node address: 0000000000106FA0 | data = 0 | next node address: null

Linked List after inserting 15 at head:
Node address: 0000000000110820 | data = 15 | next node address: 000000000010F7B0
Node address: 000000000010F7B0 | data = 9 | next node address: 000000000010F770
Node address: 000000000010F770 | data = 8 | next node address: 000000000010F730
Node address: 000000000010F730 | data = 7 | next node address: 000000000010F6F0
Node address: 000000000010F6F0 | data = 6 | next node address: 000000000010F6B0
Node address: 000000000010F6B0 | data = 5 | next node address: 000000000010F670
Node address: 000000000010F670 | data = 4 | next node address: 000000000010F630
Node address: 000000000010F630 | data = 3 | next node address: 000000000010F5F0
Node address: 000000000010F5F0 | data = 2 | next node address: 0000000000109E50
Node address: 0000000000109E50 | data = 1 | next node address: 0000000000106FA0
Node address: 0000000000106FA0 | data = 0 | next node address: null

Linked List after deleting at head:
Node address: 000000000010F7B0 | data = 9 | next node address: 000000000010F770
Node address: 000000000010F770 | data = 8 | next node address: 000000000010F730
Node address: 000000000010F730 | data = 7 | next node address: 000000000010F6F0
Node address: 000000000010F6F0 | data = 6 | next node address: 000000000010F6B0
Node address: 000000000010F6B0 | data = 5 | next node address: 000000000010F670
Node address: 000000000010F670 | data = 4 | next node address: 000000000010F630
Node address: 000000000010F630 | data = 3 | next node address: 000000000010F5F0
Node address: 000000000010F5F0 | data = 2 | next node address: 0000000000109E50
Node address: 0000000000109E50 | data = 1 | next node address: 0000000000106FA0
Node address: 0000000000106FA0 | data = 0 | next node address: null
*/