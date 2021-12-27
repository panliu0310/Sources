#include <stdio.h>
#include <stdlib.h>
typedef struct bstCDT bst;
struct bstCDT {
    int val;
    bst* left;
    bst* right;
};

bst* TreeGenerator()
{
    bst* tree = (bst*)malloc(sizeof(bst));
    tree->val = 3;
    tree->right = (bst*)malloc(sizeof(bst));
    tree->right->val = 5;
    tree->right->right = NULL;
    tree->right->left = NULL;
    tree->left = (bst*)malloc(sizeof(bst));
    tree->left->val = 2;
    tree->left->right = NULL;
    tree->left->left = (bst*)malloc(sizeof(bst));
    tree->left->left->val = 1;
    tree->left->left->right = NULL;
    tree->left->left->left = NULL;
    return tree;
}

int NumGenerator()
{
    return 4;
}

int Find_closest(bst* tree, int num);

int abs(int n) {
    if (n >= 0)
        return n;
    if (n < 0)
        return -n;
}

int main() {
    bst* tree = TreeGenerator();
    int num = NumGenerator();
    int ans = Find_closest(tree, num);
    // For this example, the ans is 3;
    printf("%d\n", ans);
    return 0;
}

// Please finish this function implementation.
int Find_closest(bst* tree, int num)
{
    int rootvalue = tree->val;
    int leftvalue, rightvalue;
    if (tree->left != NULL)
        leftvalue = Find_closest(tree->left, num);
    if (tree->right != NULL)
        rightvalue = Find_closest(tree->right, num);
    int closest = rootvalue;
    if (tree->left != NULL)
        if ((abs(leftvalue - num) < abs(rootvalue - num)) || (abs(leftvalue - num) == abs(rootvalue - num) && leftvalue < rootvalue))
            closest = leftvalue;
    if (tree->right != NULL)
        if ((abs(rightvalue - num) < abs(rightvalue - num)) || (abs(rightvalue - num) == abs(rightvalue - num) && rightvalue < rootvalue))
            closest = rightvalue;
    return closest;
}