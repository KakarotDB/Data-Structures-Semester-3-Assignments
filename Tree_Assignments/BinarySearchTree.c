#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) >= (b) ? a : b)

typedef struct TreeNode {
    int data;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
    struct TreeNode *parent;
} TreeNode;

int isEmpty(TreeNode *root) {
    if (root == NULL) {
        return 1;
    }

    return 0;
}

int insertNode(TreeNode **root, int value) {
    if (root == NULL) {
        return 0; // invalid binary search tree
    }
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

    if (newNode == NULL) {
        return 0; // memory allocation failed
    }

    newNode->data = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parent = NULL;

    if (*root == NULL) {
        *root = newNode; // first element of BST
        return 1;
    }

    TreeNode *current = *root;
    TreeNode *parentNode = NULL;

    while (current != NULL) {
        parentNode = current;

        if (value < current->data) {
            current = current->leftChild;
        } else if (value > current->data) {
            current = current->rightChild;
        } else {
            return 0; // node already exists in BST
        }
    }

    if (value < parentNode->data) {
        parentNode->leftChild = newNode;
    } else {
        parentNode->rightChild = newNode;
    }

    newNode->parent = parentNode;
    return 1;
}

int getCount(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + getCount(root->leftChild) +
           getCount(root->rightChild); // depth first search
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

int getHeight(TreeNode *root) { //by convention we will represent an empty tree with height -1
    if (root == NULL) {
        return -1; // empty tree
    }

    return 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
}

int getMax(TreeNode *root, int *maxNode) {
    if (root == NULL)
        return 0; // empty tree
    TreeNode *traversal = root;
    while (traversal->rightChild != NULL) {
        traversal = traversal->rightChild;
    }
    *maxNode = traversal->data;
    return 1;
}

int getMin(TreeNode *root, int *minNode) {
    if (root == NULL) {
        return 0; // empty tree
    }
    TreeNode *traversal = root;
    while (traversal->leftChild != NULL) {
        traversal = traversal->leftChild;
    }
    *minNode = traversal->data;
    return 1;
}

int isEqual(TreeNode *root1, TreeNode *root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1; // true
    }

    if (root1 == NULL || root2 == NULL || root1->data != root2->data) {
        return 0; // false
    }

    return isEqual(root1->leftChild, root2->leftChild) &&
           isEqual(root1->rightChild, root2->rightChild);
}

int findNode(TreeNode *root, TreeNode **found, int key) {
    *found = NULL;

    if (root == NULL || found == NULL) {
        return 0;
    }

    TreeNode *current = root;
    while (current != NULL) {
        if (key == current->data) {
            *found = current;
            return 1;
        } else if (key < current->data) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
    }
    return 0;
}

int inOrderSuccessor(TreeNode *root, int key, TreeNode **inOrderPointer) {
    TreeNode *target = NULL;

    if (findNode(root, &target, key) == 0 || inOrderPointer == NULL) {
        return 0;
    }

    if (target->rightChild != NULL) {
        TreeNode *current = target->rightChild;
        while (current->leftChild != NULL) {
            current = current->leftChild;
        }
        *inOrderPointer = current;
        return 1;
    }

    TreeNode *successor = NULL;
    TreeNode *current = target;

    while (current != NULL) {
        successor = current->parent;
        if (successor == NULL) {
            return 0;
        }
        if (current == successor->leftChild) {
            *inOrderPointer = successor;
            return 1;
        }
        current = successor;
    }
    return 0;
}

int deleteNode(TreeNode **root, int value) {
    TreeNode *toDelete = NULL;

    if (root == NULL || findNode(*root, &toDelete, value) == 0) {
        return 0; // invalid tree OR node not present in tree
    }

    // Case 1 : leaf node
    if (toDelete->leftChild == NULL && toDelete->rightChild == NULL) {
        TreeNode *parent = toDelete->parent;
        if (parent != NULL) {
            if (parent->leftChild == toDelete) {
                parent->leftChild = NULL;
            } else {
                parent->rightChild = NULL;
            }
        } else {
            *root = NULL;
        }
        free(toDelete);
        return 1;
    } // case 2 : Only one child
    else if (toDelete->leftChild == NULL) { // right subtree exists
        TreeNode *parent = toDelete->parent;
        if (parent == NULL) { // root of tree
            *root = toDelete->rightChild;
            (*root)->parent = NULL;
            free(toDelete);
            return 1;
        } else if (parent->leftChild == toDelete) {
            parent->leftChild = toDelete->rightChild;
            toDelete->rightChild->parent = parent;
            free(toDelete);
            return 1;
        } else {
            parent->rightChild = toDelete->rightChild;
            toDelete->rightChild->parent = parent;
            free(toDelete);
            return 1;
        }
    } else if (toDelete->rightChild == NULL) { // left subtree exists
        TreeNode *parent = toDelete->parent;
        if (parent == NULL) { // root of tree
            *root = toDelete->leftChild;
            (*root)->parent = NULL;
            free(toDelete);
            return 1;
        } else if (parent->leftChild == toDelete) {
            parent->leftChild = toDelete->leftChild;
            toDelete->leftChild->parent = parent;
            free(toDelete);
            return 1;
        } else {
            parent->rightChild = toDelete->leftChild;
            toDelete->leftChild->parent = parent;
            free(toDelete);
            return 1;
        }
    } else { // case 3 : toDelete has both children
        TreeNode *inOrderPointer = NULL;

        if (inOrderSuccessor(*root, value, &inOrderPointer) == 0) {
            return 0; // there must be an in ordre successor, something has gone
                      // wrong.
        }

        toDelete->data = inOrderPointer->data;
        if (inOrderPointer->leftChild == NULL &&
            inOrderPointer->rightChild == NULL) {
            TreeNode *parent = inOrderPointer->parent;
            if (parent->leftChild == inOrderPointer) {
                parent->leftChild = NULL;
            } else {
                parent->rightChild = NULL;
            }
            free(inOrderPointer);
            return 1;
        } else { // left child must be null as it is in order sucessor (minimum
                 // of right sub tree)
            TreeNode *parent = inOrderPointer->parent;
            if (parent->leftChild == inOrderPointer) {
                parent->leftChild = inOrderPointer->rightChild;
                inOrderPointer->rightChild->parent = parent;
                free(inOrderPointer);
                return 1;
            } else { // parent->rightChild == inOrderPointer
                parent->rightChild = inOrderPointer->rightChild;
                inOrderPointer->rightChild->parent = parent;
                free(inOrderPointer);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    // variable declaration zone

    int choice = -1;
    int value = 0;
    TreeNode *root = NULL;
    int max = 0;
    int min = 0;
    int n1 = 0;
    int n2 = 0;
    TreeNode *root1 = NULL, *root2 = NULL, *inOrderPointer = NULL;

    do {
        printf("Enter your choice : \n"
               "1. Check if tree is Empty\n"
               "2. Add node to tree\n"
               "3. Pre-Order traversal of tree\n"
               "4. In-Order traversal of tree\n"
               "5. Post-Order traversal of tree\n"
               "6. Height of current tree\n"
               "7. Maximum node of tree\n"
               "8. Minimum node of tree\n"
               "9. Make two trees and check for equality\n"
               "10. Check for in order successor of a node\n"
               "11. Delete a node from the tree\n"
               "0. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (isEmpty(root)) {
                printf("Tree is Empty\n");
            } else {
                printf("Tree is not empty\n");
            }
            break;
        case 2:
            printf("Enter value to insert into binary search tree : ");
            scanf("%d", &value);
            if (insertNode(&root, value)) {
                printf("Successfully inserted %d into the tree!\n", value);
            } else {
                printf("Failed to insert %d into the tree!\n", value);
            }
            break;
        case 3:
            printf("Pre order traversal : \n");
            if (preOrderTraversal(root) == 0) {
                printf("NULL");
            }
            printf("\n");
            break;
        case 4:
            printf("In order traversal : \n");
            if (inOrderTraversal(root) == 0) {
                printf("NULL");
            }
            printf("\n");
            break;
        case 5:
            printf("Post order traversal : \n");
            if (postOrderTraversal(root) == 0) {
                printf("NULL");
            }
            printf("\n");
            break;
        case 6:
            printf("Height = %d\n", getHeight(root));
            break;
        case 7:
            if (getMax(root, &max) == 1) {
                printf("Maximum value in tree is %d\n", max);
            } else {
                printf("Tree is empty!\n");
            }
            break;
        case 8:
            if (getMin(root, &min) == 1) {
                printf("Minimum value in tree is %d\n", min);
            } else {
                printf("Tree is empty!\n");
            }
            break;
        case 9:
            printf("Enter number of nodes for tree1 and tree2: ");
            scanf("%d %d", &n1, &n2);
            printf("Enter numbers into tree1 : \n");
            if (n1 != n2) {
                printf("The two trees cannot be identical if they don't have "
                       "the same number of nodes!\n");
                break;
            }
            for (int i = 0; i < n1; i++) {
                scanf("%d", &value);
                insertNode(&root1, value);
            }
            printf("Enter numbers into tree2 : \n");
            for (int i = 0; i < n2; i++) {
                scanf("%d", &value);
                insertNode(&root2, value);
            }
            if (isEqual(root1, root2)) {
                printf("Both trees are identical\n");
            } else {
                printf("Both trees are not identical\n");
            }
            break;
        case 10:
            printf("Enter node for finding inOrder Successor : ");
            scanf("%d", &value);
            if (inOrderSuccessor(root, value, &inOrderPointer) == 1) {
                printf("The in order successor is : %d\n",
                       inOrderPointer->data);
            } else {
                printf("There is no in order succcessor!\n");
            }
            break;
        case 11:
            printf("Enter node to be deleted : ");
            scanf("%d", &value);
            if (deleteNode(&root, value)) {
                printf("Successfully deleted %d from the tree !\n", value);
            } else {
                printf("Failed to delete %d from tree!\n", value);
            }
            break;
        default:
            printf("Wrong choice/Program exit!\n");
            break;
        }

    } while (choice != 0);

    return 0;
}

