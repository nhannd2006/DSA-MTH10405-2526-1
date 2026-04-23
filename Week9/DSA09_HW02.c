#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

Node *insertAscNode(Node *head, int value) {
    if (head == NULL || head->data >= value) {
        Node *newNode = makeNode(value);
        newNode->next = head;
        return newNode;
    }
    head->next = insertAscNode(head->next, value);
    return head;
}
void insertAscList(LinkedList *list, int value) {
    list->head = insertAscNode(list->head, value);
}

Node *insertDescNode(Node *head, int value) {
    if (head == NULL || head->data <= value) {
        Node *newNode = makeNode(value);
        newNode->next = head;
        return newNode;
    }
    head->next = insertDescNode(head->next, value);
    return head;
}
void insertDescList(LinkedList *list, int value) {
    list->head = insertDescNode(list->head, value);
}

Node *deleteAscNode(Node *head, int value) {
    if (head == NULL) return NULL;
    if (head->data > value) return head;
    else if (head->data == value) {
        Node *temp = head->next;
        free(head);
        return deleteAscNode(temp, value);
    }
    head->next = deleteAscNode(head->next, value);
    return head;
}
void deleteAscList(LinkedList *list, int value) {
    list->head = deleteAscNode(list->head, value);
}

Node *deleteDescNode(Node *head, int value) {
    if (head == NULL) return NULL;
    if (head->data < value) return head;
    else if (head->data == value) {
        Node *temp = head->next;
        free(head);
        return deleteDescNode(temp, value);
    }
    head->next = deleteDescNode(head->next, value);
    return head;
}
void deleteDescList(LinkedList *list, int value) {
    list->head = deleteDescNode(list->head, value);
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
    time_t t;
    srand((unsigned)time(&t));
    int value = rand() % 20;
    printf("Value = %d\n", value);
    LinkedList descList;
    initList(&descList);
    int arr[10] = {0, 10, 8, 14, 6, 4, 12, 18, 2, 16};
    for (int i = 0; i < 10; i++) {
        insertDescList(&descList, arr[i]);
    }
    printf("Descending Linked List:\n");
    printLinkedList(&descList);
    freeList(&descList);
    LinkedList ascList;
    initList(&ascList);
    for (int i = 0; i < 10; i++) {
        insertAscList(&ascList, arr[i]);
    }
    deleteAscList(&ascList, value);
    printf("Ascending Linked List:\n");
    printLinkedList(&ascList);
    freeList(&ascList);
    return 0;
}

/*
Value = 2
Descending Linked List:
Node address: 000000000065DE20 | data = 18 | next node address: 000000000065DEA0
Node address: 000000000065DEA0 | data = 16 | next node address: 000000000065DD20
Node address: 000000000065DD20 | data = 14 | next node address: 000000000065DDE0
Node address: 000000000065DDE0 | data = 12 | next node address: 0000000000659B10
Node address: 0000000000659B10 | data = 10 | next node address: 000000000065DCE0
Node address: 000000000065DCE0 | data = 8 | next node address: 000000000065DD60
Node address: 000000000065DD60 | data = 6 | next node address: 000000000065DDA0
Node address: 000000000065DDA0 | data = 4 | next node address: 000000000065DE60
Node address: 000000000065DE60 | data = 2 | next node address: 0000000000656C60
Node address: 0000000000656C60 | data = 0 | next node address: null

Ascending Linked List:
Node address: 0000000000656C60 | data = 0 | next node address: 000000000065DDA0
Node address: 000000000065DDA0 | data = 4 | next node address: 000000000065DD60
Node address: 000000000065DD60 | data = 6 | next node address: 000000000065DCE0
Node address: 000000000065DCE0 | data = 8 | next node address: 0000000000659B10
Node address: 0000000000659B10 | data = 10 | next node address: 000000000065DDE0
Node address: 000000000065DDE0 | data = 12 | next node address: 000000000065DD20
Node address: 000000000065DD20 | data = 14 | next node address: 000000000065DEA0
Node address: 000000000065DEA0 | data = 16 | next node address: 000000000065DE20
Node address: 000000000065DE20 | data = 18 | next node address: null
*/