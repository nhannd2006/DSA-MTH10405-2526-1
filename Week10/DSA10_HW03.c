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
TreeNode *closestNode(BinaryTree *tree, int target) {
    if (tree->root == NULL) return NULL;
    int minDistance = abs(tree->root->data - target);
    TreeNode *closest = tree->root;
    TreeNode *curr = tree->root;
    while (curr != NULL) {
        int currDistance = abs(curr->data - target);
        if (currDistance < minDistance) {
            minDistance = currDistance;
            closest = curr;
        }
        if (currDistance == 0) break;
        if (target < curr->data) curr = curr->left;
        else if (target > curr->data) curr = curr->right;
    }
    return closest;
}

int main() {
    BinaryTree tree;
    initBinaryTree(&tree);
    int arr2[11] = {50, 17, 76, 9, 23, 54, 14, 19, 72, 12, 67};
    for (int i = 0; i < 11; i++) {
        insertSearchTree(&tree, arr2[i]);
    }
    printf("Original tree:\n");
    printInOrderTree(tree.root);
    printf("\n");
    printf(" >> 3.1. Number of nodes in the shortest path (min depth): %d\n", minBranchesTree(&tree));
    printf(" >> 3.2. Level with maximum number of nodes: %d\n", maxLevel(&tree));
    int sum1Child = sumOneChild(tree.root);
    int sum1LeftChild = sumOneLeftChild(tree.root);
    printf(" >> 3.3. Sum of nodes with exactly one child: %d\n", sum1Child);
    printf(" >> 3.4. Difference of Sum One Child & Sum Left Child Only: %d\n", sum1Child - sum1LeftChild);
    TreeNode *closest = closestNode(&tree, sum1Child - sum1LeftChild);
    printf(" >> 3.5. Node closest to value %d: %d (at %p)\n", sum1Child - sum1LeftChild, closest->data, closest);
    freeBinaryTree(&tree);
    return 0;
}

/*
Original tree:
9 12 14 17 19 23 50 54 67 72 76 
 >> 3.1. Number of nodes in the shortest path (min depth): 4
 >> 3.2. Level with maximum number of nodes: 2
 >> 3.3. Sum of nodes with exactly one child: 248
 >> 3.4. Difference of Sum One Child & Sum Left Child Only: 63
 >> 3.5. Node closest to value 63: 67 (at 000001B810C6FDF0)
*/