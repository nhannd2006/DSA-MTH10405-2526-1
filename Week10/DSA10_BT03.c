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

int heightTreeNode(TreeNode *root) {
    if (root == NULL) return 0;
    int lHeight = heightTreeNode(root->left);
    int rHeight = heightTreeNode(root->right);
    return ((lHeight > rHeight) ? lHeight : rHeight) + 1;
}
int heightBinaryTree(BinaryTree *tree) {
    return heightTreeNode(tree->root);
}

void levelOrderTraversal(TreeNode *root, int level) {
    if (root == NULL) return;
    if (level == 1) printf("%d ", root->data);
    else if (level > 1) {
        levelOrderTraversal(root->left, level - 1);
        levelOrderTraversal(root->right, level - 1);
    }
}
void printLevelOrderTree(BinaryTree *tree) {
    int height = heightBinaryTree(tree);
    for (int i = 1; i <= height; i++) {
        levelOrderTraversal(tree->root, i);
        printf("\n");
    }
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

TreeNode *searchTreeNode(TreeNode *root, int key) {
    if (root == NULL) return NULL;
    if (root->data == key) return root;
    else if (root->data > key) return searchTreeNode(root->left, key);
    else return searchTreeNode(root->right, key);
}
TreeNode *searchBinaryTree(BinaryTree *tree, int key) {
    return searchTreeNode(tree->root, key);
}

int main() {
    BinaryTree tree;
    int value;
    TreeNode *found;
    initBinaryTree(&tree);
    int arr[14] = {50, 25, 75, 10, 33, 56, 89, 4, 11, 40, 52, 61, 82, 95};
    printf("Binary tree: ");
    for (int i = 0; i < 14; i++) {
        printf("%d ", arr[i]);
        insertBinaryTree(&tree, arr[i]);
    }
    printf("\n");
    printf("In-order binary tree:\n");
    printLevelOrderTree(&tree);
    printf("\n");
    value = 75;
    found = searchBinaryTree(&tree, value);
    if (found == NULL) printf("Not found %d.\n", value);
    else printf("Found %d at %p.\n", value, found);
    value = 89;
    found = searchBinaryTree(&tree, value);
    if (found == NULL) printf("Not found %d.\n", value);
    else printf("Found %d at %p.\n", value, found);
    value = 33;
    found = searchBinaryTree(&tree, value);
    if (found == NULL) printf("Not found %d.\n", value);
    else printf("Found %d at %p.\n", value, found);
    value = 61;
    found = searchBinaryTree(&tree, value);
    if (found == NULL) printf("Not found %d.\n", value);
    else printf("Found %d at %p.\n", value, found);
    value = 35;
    found = searchBinaryTree(&tree, value);
    if (found == NULL) printf("Not found %d.\n", value);
    else printf("Found %d at %p.\n", value, found);
    return 0;
}

/*
Binary tree: 50 25 75 10 33 56 89 4 11 40 52 61 82 95 
In-order binary tree: 4 10 11 25 33 40 50 52 56 61 75 82 89 95
Found 75 at 00000000007E98B0.
Found 89 at 00000000007F04F0.
Found 33 at 00000000007E9950.
Found 61 at 00000000007F0680.
Not found 35.
*/