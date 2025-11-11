#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
} TreeNode;

int preOrderIndex =
    0; // global variable so that it persists across all recursive calls

int newNode(TreeNode **node, int data) {
    if (node == NULL) {
        return 0;
    }

    *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (*node == NULL) {
        return 0; // malloc failed
    }

    (*node)->data = data;
    (*node)->leftChild = NULL;
    (*node)->rightChild = NULL;

    return 1;
}

int findPosition(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// inOrderStart is the starting index of the current inorder subarray, vice
// versa for inOrderEnd
TreeNode *getTreeInPreOrderHelper(int inOrder[], int preOrder[],
                                  int inOrderStart, int inOrderEnd) {
    if (inOrderStart > inOrderEnd) {
        return NULL; // base case -> current in order Subarray is empty
    }

    int rootValue = preOrder[preOrderIndex++];
    TreeNode *root = NULL;

    if (newNode(&root, rootValue) == 0) {
        fprintf(stderr, "Failed to allocate new node!\n");
        exit(EXIT_FAILURE);
    }

    if (inOrderStart == inOrderEnd) {
        return root; // current subarray has only one element left
    }

    int inOrderIndex =
        findPosition(inOrder, inOrderStart, inOrderEnd, rootValue);

    if (inOrderIndex == -1) {
        fprintf(stderr,
                "Error : value %d from preOrder not found in in order subarray "
                "[%d, %d]!\n",
                rootValue, inOrderStart, inOrderEnd);
        free(root);
        exit(EXIT_FAILURE);
    }

    // recursively constructing the left subTree using the left part of the in
    // order subarray
    root->leftChild = getTreeInPreOrderHelper(inOrder, preOrder, inOrderStart,
                                              inOrderIndex - 1);

    // recursively constructing the right subTree using the right part of the in
    // order subarray
    root->rightChild = getTreeInPreOrderHelper(inOrder, preOrder,
                                               inOrderIndex + 1, inOrderEnd);

    return root;
}

TreeNode *getTreeInPreOrder(int a[], int aSize, int b[], int bSize) {
    if (aSize <= 0 || bSize <= 0 || aSize != bSize) {
        fprintf(stderr, "Error : Invalid array size/mismatch\n");
        return NULL;
    }

    preOrderIndex = 0;

    return getTreeInPreOrderHelper(a, b, 0, aSize - 1);
}

TreeNode *getTreeInPostOrderHelper(int inOrder[], int postOrder[],
                                   int inOrderStart, int inOrderEnd,
                                   int *postOrderIndex) {
    if (inOrderStart > inOrderEnd) {
        return NULL; // base case
    }

    int rootValue = postOrder[(*postOrderIndex)--];
    TreeNode *root = NULL;

    if (newNode(&root, rootValue) == 0) {
        fprintf(stderr, "Failed to allocate new node!\n");
        exit(EXIT_FAILURE);
    }

    if (inOrderStart == inOrderEnd) {
        return root;
    }

    int inOrderIndex =
        findPosition(inOrder, inOrderStart, inOrderEnd, rootValue);
    if (inOrderIndex == -1) {
        fprintf(stderr,
                "Error : value %d from postOrder not found in inOrder "
                "Subarray[%d, %d]",
                rootValue, inOrderStart, inOrderEnd);
        free(root);
        exit(EXIT_FAILURE);
    }
    root->rightChild = getTreeInPostOrderHelper(
        inOrder, postOrder, inOrderIndex + 1, inOrderEnd, postOrderIndex);
    root->leftChild = getTreeInPostOrderHelper(
        inOrder, postOrder, inOrderStart, inOrderIndex - 1, postOrderIndex);

    return root;
}

TreeNode *getTreeInPostOrder(int a[], int aSize, int b[], int bSize) {
    if (aSize <= 0 || bSize <= 0 || aSize != bSize) {
        fprintf(stderr, "Error: Invalid array sizes/size mismatch\n");
        return NULL;
    }

    int postIndex = aSize - 1;

    return getTreeInPostOrderHelper(a, b, 0, aSize - 1, &postIndex);
}

int inOrderTraversal(TreeNode *root) { // left -> root -> right
    if (root == NULL) {
        return 0; // empty tree
    }

    inOrderTraversal(root->leftChild);

    printf("%d ", root->data);

    inOrderTraversal(root->rightChild);

    return 1;
}

int preOrderTraversal(TreeNode *root) { // root -> left -> right
    if (root == NULL) {
        return 0; // empty tree
    }

    printf("%d ", root->data);

    preOrderTraversal(root->leftChild);
    preOrderTraversal(root->rightChild);

    return 1;
}

int postOrderTraversal(TreeNode *root) { // left -> right -> root
    if (root == NULL) {
        return 0; // empty tree
    }

    postOrderTraversal(root->leftChild);
    postOrderTraversal(root->rightChild);

    printf("%d ", root->data);

    return 1;
}

void freeTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->leftChild);
    freeTree(root->rightChild);
    free(root);
}

int main() {
    int inorder[] = {4, 2, 5, 1, 6, 3, 7};
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    printf("Building the tree from inOrder and PreOrder : \n");

    printf("Input InOrder: \n");

    for (int i = 0; i < n; i++)
        printf("%d ", inorder[i]);
    printf("\n");

    printf("Input preOrder : \n");
    for (int i = 0; i < n; i++)
        printf("%d ", preorder[i]);
    printf("\n");

    TreeNode *preOrderBuilding = getTreeInPreOrder(inorder, n, preorder, n);

    printf("Verification : \n");
    printf("Inorder traversal of built tree : \n");
    inOrderTraversal(preOrderBuilding);
    printf("\n");

    printf("PreOrder traversal of built tree : \n");
    preOrderTraversal(preOrderBuilding);
    printf("\n");

    freeTree(preOrderBuilding);
    preOrderBuilding = NULL;

    printf("\n");

    printf("Building the tree from inOrder and postOrder : \n");

    printf("Input InOrder: \n");

    for (int i = 0; i < n; i++)
        printf("%d ", inorder[i]);
    printf("\n");

    printf("Input postOrder : \n");

    for (int i = 0; i < n; i++) {
        printf("%d ", postorder[i]);
    }
    printf("\n");

    TreeNode *PostOrderBuilding = getTreeInPostOrder(inorder, n, postorder, n);
    printf("Verification : \n");

    printf("In order of built tree : \n");
    inOrderTraversal(PostOrderBuilding);
    printf("\n");

    printf("Post order of built tree : \n");
    postOrderTraversal(PostOrderBuilding);
    printf("\n");

    freeTree(PostOrderBuilding);
    PostOrderBuilding = NULL;

    return 0;
}

