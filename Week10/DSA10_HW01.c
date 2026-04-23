#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct {
    TreeNode *root;
} BinaryTree;

TreeNode *makeTreeNode(int data) {
    TreeNode *tree = (TreeNode *) malloc(sizeof(TreeNode));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
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

typedef struct {
    TreeNode* arr[MAX];
    int head, tail;
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

void enqueue(CircQueue *q, TreeNode *value) {
    if (isFull(q)) {
        printf("Queue is full.\n");
        return;
    }
    if (isEmpty(q)) q->head = q->tail = 0;
    else q->tail = (q->tail + 1) % MAX;
    q->arr[q->tail] = value;
}

TreeNode* dequeue(CircQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return NULL;
    }
    TreeNode *value = q->arr[q->head];
    if (q->head == q->tail) q->head = q->tail = -1;
    else q->head = (q->head + 1) % MAX;
    return value;
}

int queueSize(CircQueue *q) {
    if (isEmpty(q)) return 0;
    if (q->tail >= q->head) return q->tail - q->head + 1;
    else return MAX - q->head + q->tail + 1;
}

// ========================================
// 1.1: COMPLETE BINARY TREE
void insertCompleteTree(BinaryTree *tree, int value) {
    if (tree->root == NULL) {
        tree->root = makeTreeNode(value);
        return;
    }
    CircQueue q;
    initQueue(&q);
    enqueue(&q, tree->root);
    while (!isEmpty(&q)) {
        TreeNode *temp = dequeue(&q);
        if (temp->left != NULL) enqueue(&q, temp->left);
        else {
            temp->left = makeTreeNode(value);
            return;
        }
        if (temp->right != NULL) enqueue(&q, temp->right);
        else {
            temp->right = makeTreeNode(value);
            return;
        }
    }
}

void printLevelOrderTree(TreeNode *root) {
    if (root == NULL) return;
    CircQueue q;
    initQueue(&q);
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        int len = queueSize(&q);
        for (int i = 0; i < len; i++) {
            TreeNode *curr = dequeue(&q);
            printf("%d ", curr->data);
            if (curr->left != NULL) enqueue(&q, curr->left);
            if (curr->right != NULL) enqueue(&q, curr->right);
        }
        printf("\n");
    }
}

// ========================================
// 1.2 - 1.3: BINARY SEARCH TREE
TreeNode *insertSearchNode(TreeNode *root, int value) {
    if (root == NULL) return makeTreeNode(value);
    if (value < root->data) root->left = insertSearchNode(root->left, value);
    else if (value > root->data) root->right = insertSearchNode(root->right, value);
    return root;
}

void insertSearchTree(BinaryTree *tree, int value) {
    tree->root = insertSearchNode(tree->root, value);
}

void printInOrderTree(TreeNode *root) {
    if (root == NULL) return;
    printInOrderTree(root->left);
    printf("%d ", root->data);
    printInOrderTree(root->right);
}

// ========================================
// 1.4: GENERAL BINARY TREE
void buildGeneralTree_4(BinaryTree *tree) {
    initBinaryTree(tree);
    // Level 1
    tree->root = makeTreeNode(3);
    // Level 2
    tree->root->left = makeTreeNode(1);
    tree->root->right = makeTreeNode(10);
    // Level 3
    tree->root->left->left = makeTreeNode(13);
    tree->root->left->right = makeTreeNode(5);
    tree->root->right->left = makeTreeNode(11);
    tree->root->right->right = makeTreeNode(16);
    // Level 4
    tree->root->left->right->left = makeTreeNode(6); // Con trái của 5
    tree->root->right->right->left = makeTreeNode(15); // Con trái 16
    tree->root->right->right->right = makeTreeNode(2); // Con phải 16
    
    // Level 5
    tree->root->right->right->left->left = makeTreeNode(9); // Con trái 15
    tree->root->right->right->left->right = makeTreeNode(4); // Con phải 15
}

int main() {
    BinaryTree tree;
    initBinaryTree(&tree);
    printf("----- 1. COMPLETE BINARY TREE\n");
    for (int i = 1; i <= 15; i++) {
        insertCompleteTree(&tree, i);
    }
    printLevelOrderTree(tree.root);
    printf("\n");
    freeBinaryTree(&tree);
    printf("----- 2. BINARY SEARCH TREE\n");
    int arr2[11] = {50, 17, 76, 9, 23, 54, 14, 19, 72, 12, 67};
    for (int i = 0; i < 11; i++) {
        insertSearchTree(&tree, arr2[i]);
    }
    printInOrderTree(tree.root);
    printf("\n\n");
    freeBinaryTree(&tree);
    printf("----- 3. BINARY SEARCH TREE\n");
    int arr3[11] = {15, 11, 26, 8, 12, 20, 30, 6, 9, 14, 35};
    for (int i = 0; i < 11; i++) {
        insertSearchTree(&tree, arr3[i]);
    }
    printInOrderTree(tree.root);
    printf("\n\n");
    freeBinaryTree(&tree);
    printf("----- 4. GENERAL BINARY TREE\n");
    buildGeneralTree_4(&tree);
    printLevelOrderTree(tree.root);
    printf("\n");
    freeBinaryTree(&tree);
    return 0;
}

/*
----- 1. COMPLETE BINARY TREE
1 
2 3 
4 5 6 7 
8 9 10 11 12 13 14 15 

----- 2. BINARY SEARCH TREE
9 12 14 17 19 23 50 54 67 72 76 

----- 3. BINARY SEARCH TREE
6 8 9 11 12 14 15 20 26 30 35 

----- 4. GENERAL BINARY TREE
3
1 10
13 5 11 16
6 15 2
9 4
*/