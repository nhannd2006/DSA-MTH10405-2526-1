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

TreeNode *makeNode(int data) {
    TreeNode *tree = (TreeNode *) malloc(sizeof(TreeNode));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void printTree(TreeNode *root) {
    if (root) {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    } else return;
}

void initBinaryTree(BinaryTree *tree) {
    tree->root = NULL;
}

TreeNode *insertTreeNode(TreeNode *root, int value) {
    if (root == NULL) {
        return makeNode(value);
    }
    if (value < root->data) {
        root->left = insertTreeNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertTreeNode(root->right, value);
    }
    return root;
}

void insertBinaryTree(BinaryTree *tree, int value) {
    tree->root = insertTreeNode(tree->root, value);
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

void enqueue(CircQueue *q, TreeNode *x) {
    if (isFull(q)) {
        printf("Queue is full.\n");
        return;
    }
    if (isEmpty(q)) q->head = q->tail = 0;
    else q->tail = (q->tail + 1) % MAX;
    q->arr[q->tail] = x;
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

void levelOrderTree(TreeNode *root) {
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

int main() {
    BinaryTree tree;
    initBinaryTree(&tree);
    int arr1[7] = {4, 6, 2, 3, 5, 1, 7};
    for (int i = 0; i < 7; i++) {
        insertBinaryTree(&tree, arr1[i]);
    }
    printTree(tree.root);
    printf("\n");
    initBinaryTree(&tree);
    int arr2[9] = {8, 10, 3, 6, 14, 1, 7, 13, 4};
    for (int i = 0; i < 9; i++) {
        insertBinaryTree(&tree, arr2[i]);
    }
    printTree(tree.root);
    printf("\n");
    initBinaryTree(&tree);
    int arr[14] = {50, 25, 75, 10, 33, 56, 89, 4, 11, 40, 52, 61, 82, 95};
    for (int i = 0; i < 14; i++) {
        insertBinaryTree(&tree, arr[i]);
    }
    levelOrderTree(tree.root);
    printf("\n");
    return 0;
}

/*
1 2 3 4 5 6 7 
1 3 4 6 7 8 10 13 14 
50 
25 75 
10 33 56 89 
4 11 40 52 61 82 95
*/