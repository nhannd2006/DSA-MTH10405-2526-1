/*
Xây dựng và cài đặt cấu trúc danh sách liên kết đơn để lưu trữ một bảng tin (Newsfeed) gồm các tiêu đề các bài đăng tin.
Chương trình cho phép thêm vào đầu và tìm kiếm bài đăng trong Newsfeed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char title[MAX];
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

LinkedList newsfeed;

void initList(LinkedList *list) {
    list->head = NULL;
}

Node *makeNode(char *value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->title, value);
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

void insertHeadList(LinkedList *list, char *value) {
    Node *newNode = makeNode(value);
    newNode->next = list->head;
    list->head = newNode;
}

Node *searchList(LinkedList *list, char *key) {
    Node *curr = list->head;
    while (curr != NULL) {
        if (strstr(curr->title, key) != NULL) return curr;
        curr = curr->next;
    }
    return NULL;
}

void menuInsert() {
    system("cls");
    printf("--- INSERT NEWSFEED ---\n");
    char title[MAX];
    printf("Enter title to insert: ");   
    fgets(title, MAX, stdin);
    title[strcspn(title, "\n")] = '\0';
    insertHeadList(&newsfeed, title);
    printf("Insert successful.\n");
    system("pause");
}

void menuSearch() {
    system("cls");
    printf("--- SEARCH TITLE ---\n");
    char key[MAX];
    printf("Enter ket of title to search: ");   
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = '\0';
    searchList(&newsfeed, key);
    Node *found = searchList(&newsfeed, key);
    if (found != NULL) printf("Found %s\n", found->title);
    else printf("Not found %s\n", key);
    system("pause");
}

void menuDisplay() {
    system("cls");
    printf("--- ALL TITLES ---\n");
    Node *node = newsfeed.head;
    while (node) {
        printf("%s", node->title);
        if (node->next != NULL) printf(" | ");
        node = node->next;
    }
    printf("\n");
    system("pause");
}


int main() {
    initList(&newsfeed);
    int choice;
    do {
        system("cls");
        printf("=== NEWSFEED ===\n");
        printf("1. Insert newsfeed.\n");
        printf("2. Search newsfeed.\n");
        printf("3. Display newfeed.\n");
        printf("0. Exit.\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1: 
                menuInsert();
                break;
            case 2:
                menuSearch();
                break;
            case 3:
                menuDisplay();
                break;
            case 0:
                printf("SEE YOU AGAIN!\n");
                system("pause");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 0);
    freeList(&newsfeed);
    return 0;
}
