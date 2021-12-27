#include <stdio.h>
#include <stdlib.h>
typedef struct btCDT bt;
struct btCDT {
    int val;
    bt* left;
    bt* right;
};

bt* Mirror(bt* tree);

void PrintTree(bt* tree);

bt* TreeGenerator()
{
    bt* tree = (bt*)malloc(sizeof(bt));
    tree->val = 102;
    tree->right = (bt*)malloc(sizeof(bt));
    tree->right->val = 81;
    tree->right->right = (bt*)malloc(sizeof(bt));
    tree->right->right->val = 94;
    tree->right->right->right = NULL;
    tree->right->right->left = NULL;
    tree->right->left = (bt*)malloc(sizeof(bt));
    tree->right->left->val = 76;
    tree->right->left->right = NULL;
    tree->right->left->left = (bt*)malloc(sizeof(bt));
    tree->right->left->left->val = 1;
    tree->left = (bt*)malloc(sizeof(bt));
    tree->left->val = 43;
    tree->left->right = NULL;
    tree->left->left = NULL;
    return tree;
}
int main() {
    bt* tree = TreeGenerator();
    PrintTree(tree);
    printf("\n");
    tree = Mirror(tree);
    PrintTree(tree);
    return 0;
}

bt* Mirror(bt* tree)
{
    bt* temp = tree->right;
    tree->right = tree->left;
    tree->left = temp;
    if (tree->right != NULL)
        tree->right = Mirror(tree->right);
    if (tree->left != NULL)
        tree->left = Mirror(tree->left);
    return tree;
}

//This function is for checking answer.
void PrintTree(bt* tree) {
    printf("%d ", tree->val);
    if (tree->left != NULL)
        PrintTree(tree->left);
    if (tree->right != NULL)
        PrintTree(tree->right);
}