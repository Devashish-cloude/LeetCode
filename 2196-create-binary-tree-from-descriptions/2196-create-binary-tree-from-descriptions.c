
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VAL 100001

struct TreeNode* createBinaryTree(int** descriptions,
                                 int descriptionsSize,
                                 int* descriptionsColSize) {
    (void)descriptionsColSize;

    struct TreeNode* nodes[MAX_VAL] = {NULL};
    bool isChild[MAX_VAL] = {false};

    for (int i = 0; i < descriptionsSize; i++) {
        int parent = descriptions[i][0];
        int child = descriptions[i][1];
        int isLeft = descriptions[i][2];

        if (nodes[parent] == NULL) {
            nodes[parent] = malloc(sizeof(struct TreeNode));
            nodes[parent]->val = parent;
            nodes[parent]->left = NULL;
            nodes[parent]->right = NULL;
        }

        if (nodes[child] == NULL) {
            nodes[child] = malloc(sizeof(struct TreeNode));
            nodes[child]->val = child;
            nodes[child]->left = NULL;
            nodes[child]->right = NULL;
        }

        if (isLeft == 1)
            nodes[parent]->left = nodes[child];
        else
            nodes[parent]->right = nodes[child];

        isChild[child] = true;
    }

    for (int i = 1; i < MAX_VAL; i++) {
        if (nodes[i] != NULL && !isChild[i])
            return nodes[i];
    }

    return NULL;
}
