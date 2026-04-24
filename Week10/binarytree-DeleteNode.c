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

void inOrderTraversal(TreeNode *root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

TreeNode *insertTreeNode(TreeNode *root, int value) {
    if (root == NULL) return makeTreeNode(value);
    if (value < root->data) root->left = insertTreeNode(root->left, value);
    else if (value > root->data) root->right = insertTreeNode(root->right, value);
    return root;
}
void insertBinaryTree(BinaryTree *tree, int value) {
    tree->root = insertTreeNode(tree->root, value);
}

// find the smallest node in right subtree
TreeNode *getSuccessor(TreeNode *root) {
    root = root->right;
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode *deleteTreeNode(TreeNode *root, int value) {
    if (root == NULL) return NULL;
    if (value < root->data) root->left = deleteTreeNode(root->left, value);
    else if (value > root->data) root->right = deleteTreeNode(root->right, value);
    else {
        // CASE 1: node with 0 or 1 child
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // CASE 2: node with 2 children
        TreeNode *succ = getSuccessor(root);
        root->data = succ->data;
        root->right = deleteTreeNode(root->right, succ->data);
    }
    return root;
}

void deleteBinaryTree(BinaryTree *tree, int value) {
    tree->root = deleteTreeNode(tree->root, value);
}

int main() {
    BinaryTree tree;
    int value;
    initBinaryTree(&tree);
    int arr[14] = {50, 25, 75, 10, 33, 56, 89, 4, 11, 40, 52, 61, 82, 95};
    printf("Binary tree: ");
    for (int i = 0; i < 14; i++) {
        printf("%d ", arr[i]);
        insertBinaryTree(&tree, arr[i]);
    }
    printf("\n");
    printf("In-order binary tree: ");
    inOrderTraversal(tree.root);
    printf("\n");
    value = 35;
    deleteBinaryTree(&tree, value);
    printf("After deleting %d: ", value);
    inOrderTraversal(tree.root);
    printf("\n");
    value = 61;
    deleteBinaryTree(&tree, value);
    printf("After deleting %d: ", value);
    inOrderTraversal(tree.root);
    printf("\n");
    value = 33;
    deleteBinaryTree(&tree, value);
    printf("After deleting %d: ", value);
    inOrderTraversal(tree.root);
    printf("\n");
    value = 89;
    deleteBinaryTree(&tree, value);
    printf("After deleting %d: ", value);
    inOrderTraversal(tree.root);
    printf("\n");
    value = 75;
    deleteBinaryTree(&tree, value);
    printf("After deleting %d: ", value);
    inOrderTraversal(tree.root);
    printf("\n");
}

/*
Binary tree: 50 25 75 10 33 56 89 4 11 40 52 61 82 95 
In-order binary tree: 4 10 11 25 33 40 50 52 56 61 75 82 89 95
After deleting 35: 4 10 11 25 33 40 50 52 56 61 75 82 89 95
After deleting 61: 4 10 11 25 33 40 50 52 56 75 82 89 95
After deleting 33: 4 10 11 25 40 50 52 56 75 82 89 95
After deleting 89: 4 10 11 25 40 50 52 56 75 82 95
After deleting 75: 4 10 11 25 40 50 52 56 82 95
*/