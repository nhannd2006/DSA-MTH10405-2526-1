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
// 1: Số lượng phần tử tại nhánh từ root đến leaf có số phần tử ít nhất
int minBranches(TreeNode *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    if (root->left == NULL) return 1 + minBranches(root->right);
    if (root->right == NULL) return 1 + minBranches(root->left);
    int leftMin = minBranches(root->left);
    int rightMin = minBranches(root->right);
    return ((leftMin < rightMin) ? leftMin : rightMin) + 1;
}
int minBranchesTree(BinaryTree *tree) {
    return minBranches(tree->root);
}

// ========================================
// 2: Level có nhiều phân tử nhất trong cây
void countNodesAtLevel(TreeNode *root, int level, int *count) {
    if (root == NULL) return;
    count[level]++;
    countNodesAtLevel(root->left, level + 1, count);
    countNodesAtLevel(root->right, level + 1, count);
}
int heightTreeNode(TreeNode *root) {
    if (root == NULL) return 0;
    int lHeight = heightTreeNode(root->left);
    int rHeight = heightTreeNode(root->right);
    return ((lHeight > rHeight) ? lHeight : rHeight) + 1;
}
int heightBinaryTree(BinaryTree *tree) {
    return heightTreeNode(tree->root);
}
int maxLevel(BinaryTree *tree) {
    if (tree->root == NULL) return -1;
    int height = heightBinaryTree(tree);
    int count[MAX] = {0};
    countNodesAtLevel(tree->root, 0, count);
    int maxCount = 0;
    int maxLevel = 0;
    for (int i = 0; i < height; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            maxLevel = i;
        }
    }
    return maxLevel;
}

// ========================================
// 3: Tính tổng giá trị các node chỉ có 1 node con
int sumOneChild(TreeNode *root) {
    if (root == NULL) return 0;
    int sum = 0;
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) sum += root->data;
    sum += sumOneChild(root->left) + sumOneChild(root->right);
    return sum;
}

// ========================================
// 4: Tính hiệu các giá trị tìm được ở [3] trừ đi tổng các giá trị của các node chỉ có một node bên trái
int sumOneLeftChild(TreeNode *root) {
    if (root == NULL) return 0;
    int sum = 0;
    if (root->left != NULL && root->right == NULL) sum += root->data;
    sum += sumOneLeftChild(root->left) + sumOneLeftChild(root->right);
    return sum;
}

// ========================================
// 4: Tìm node gần giá trị cho trước nhất
TreeNode *closestNode(TreeNode *root, int target) {
    if (root == NULL) return NULL;
    TreeNode *leftClosest = closestNode(root->left, target);
    TreeNode *rightClosest = closestNode(root->right, target);
    TreeNode *closest = root;
    int minDistance = abs(root->data - target);
    if (leftClosest != NULL) {
        int leftDistance = abs(leftClosest->data - target);
        if (leftDistance < minDistance) {
            minDistance = leftDistance;
            closest = leftClosest;
        }
    }
    if (rightClosest != NULL) {
        int rightDistance = abs(rightClosest->data - target);
        if (rightDistance < minDistance) {
            minDistance = rightDistance;
            closest = rightClosest;
        }
    }
    return closest;
}


