#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };

//       15
//     4    20
//   1   16    25

int main(void) {
    TreeNode* n1, * n2, * n3;   // n1은 n2, n3의 부모

    n1 = (TreeNode*)malloc(sizeof(TreeNode));
    n2 = (TreeNode*)malloc(sizeof(TreeNode));
    n3 = (TreeNode*)malloc(sizeof(TreeNode));

    n1->data = 10;
    n1->left = n2;
    n1->right = n3;
    n2->data = 20;
    n2->left = NULL;
    n2->right = NULL;
    n2->data = 30;
    n2->left = NULL;
    n2->right = NULL;

    free(n1);
    free(n2);
    free(n3);

    
    return 0;
}