/*
Xây dựng và cài đặt một cây nhị phân tìm kiếm để lưu trữ danh bạ gồm tên và điện thoại của người cần liên hệ.
Chương trình cho phép thêm một liên hệ và tìm kiếm số điện thoại dựa trên tên của người cần liên hệ.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct TreeNode {
    char name[MAX];
    char phone[15];
    struct TreeNode *left, *right;
} TreeNode;

typedef struct {
    TreeNode *root;
} BinaryTree;

BinaryTree phonebook;

// ========================================
// CORE NODE / TREE FUNCTIONS

TreeNode *makeTreeNode(char name[], char phone[]) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    strcpy(node->name, name);
    strcpy(node->phone, phone);
    node->left = node->right = NULL;
    return node;
}

void initBinaryTree(BinaryTree *tree) {
    tree->root = NULL;
}

void freeTreeNode(TreeNode *root) {
    if (root == NULL) return;
    freeTreeNode(root->left);
    freeTreeNode(root->right);
    free(root);
}

void freeBinaryTree(BinaryTree *tree) {
    freeTreeNode(tree->root);
    tree->root = NULL;
}

// ========================================
// INSERT — BST keyed by name

TreeNode *insertTreeNode(TreeNode *root, char name[], char phone[]) {
    if (root == NULL) return makeTreeNode(name, phone);
    int cmp = strcmp(name, root->name);
    if (cmp < 0) root->left  = insertTreeNode(root->left,  name, phone);
    else if (cmp > 0) root->right = insertTreeNode(root->right, name, phone);
    return root;
}

void insertBinaryTree(BinaryTree *tree, char name[], char phone[]) {
    tree->root = insertTreeNode(tree->root, name, phone);
}

// ========================================
// SEARCH — BST keyed by name

TreeNode *searchTreeNode(TreeNode *root, char *key) {
    if (root == NULL) return NULL;
    int cmp = strcmp(key, root->name);
    if (cmp == 0) return root;
    else if (cmp < 0) return searchTreeNode(root->left,  key);
    else              return searchTreeNode(root->right, key);
}

TreeNode *searchBinaryTree(BinaryTree *tree, char *key) {
    return searchTreeNode(tree->root, key);
}

// ========================================
// MENU FUNCTIONS

void menuAdd() {
    system("cls");
    printf("--- ADD CONTACT ---\n");
    char name[MAX], phone[15];
    printf("Enter name: ");
    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter phone: ");
    fgets(phone, 15, stdin);
    phone[strcspn(phone, "\n")] = '\0';
    insertBinaryTree(&phonebook, name, phone);
    printf("Contact added successfully.\n");
    system("pause");
}

void menuSearch() {
    system("cls");
    printf("--- SEARCH CONTACT ---\n");
    char name[MAX];
    printf("Enter name to search: ");
    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = '\0';
    TreeNode *found = searchBinaryTree(&phonebook, name);
    if (found != NULL) printf("Found: %s - %s\n", found->name, found->phone);
    else printf("Not found: %s\n", name);
    system("pause");
}

// ========================================
// MAIN

int main() {
    initBinaryTree(&phonebook);
    int choice;
    do {
        system("cls");
        printf("=== PHONEBOOK ===\n");
        printf("1. Add contact.\n");
        printf("2. Search contact.\n");
        printf("0. Exit.\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                menuAdd();
                break;
            case 2:
                menuSearch();
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
    freeBinaryTree(&phonebook);
    return 0;
}
