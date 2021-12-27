#include <stdio.h>
#include <stdlib.h>

typedef struct bstCDT bst;
struct bstCDT {
    int val;
    bst* left;
    bst* right;
    int height;
};

bst* TreeGenerator()
{
    bst* tree = (bst*)malloc(sizeof(bst));
    tree->val = 3;
    tree->height = 2;
    tree->right = (bst*)malloc(sizeof(bst));
    tree->right->val = 4;
    tree->height = 0;
    tree->right->right = NULL;
    tree->right->left = NULL;
    tree->left = (bst*)malloc(sizeof(bst));
    tree->left->val = 2;
    tree->left->height = 1;
    tree->left->right = NULL;
    tree->left->left = (bst*)malloc(sizeof(bst));
    tree->left->left->val = 1;
    tree->left->left->height = 0;
    tree->left->left->right = NULL;
    tree->left->left->left = NULL;
    return tree;
}

int position = 0; int array[300];

//Checking by preorder traversal
void PrintTree(bst* tree) {
    printf("%d ", tree->val);
    if (tree->left != NULL)
        PrintTree(tree->left);
    if (tree->right != NULL)
        PrintTree(tree->right);
}

//Build into array by inorder traversal such that it is sorted automatically
void TreeBuildArray(bst* tree, int array[300]) {
    if (tree->left != NULL)
        TreeBuildArray(tree->left, array);
    array[position++] = tree->val;
    if (tree->right != NULL)
        TreeBuildArray(tree->right, array);
}

bst* ArrayBuildTree(int array[300], int start, int end) {
    int middle = (start + end) / 2;
    if (start > end)
        return NULL;
    bst* temp = (bst*)malloc(sizeof(bst));
    temp->val = array[middle];
    if (start != end && start != end - 1)
        temp->left = ArrayBuildTree(array, start, middle - 1);
    if (start != end)
        temp->right = ArrayBuildTree(array, middle + 1, end);
    return temp;
}

bst* Rebuild(bst* tree);

int main() {
    bst* tree = TreeGenerator();
    PrintTree(tree);
    tree = Rebuild(tree);
    PrintTree(tree);
    return 0;
}

bst* Rebuild(bst* tree)
{
    TreeBuildArray(tree, array);
    bst* temp = (bst*)malloc(sizeof(bst));
    temp = ArrayBuildTree(array, 0, position - 1);
    return temp;
}