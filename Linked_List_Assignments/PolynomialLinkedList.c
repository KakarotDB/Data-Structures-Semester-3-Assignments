#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coefficient;
    int exponent;
    struct node *next;
} node;

int insertNode(node **start, int coefficient, int exponent) {
    if (start == NULL)
        return 0;

    node *newNode = (node *)malloc(sizeof(node));

    if (newNode == NULL) {
        return 0; // memory allocation failed
    }

    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;

    // insert to starting of list / null list
    if (*start == NULL || exponent > (*start)->exponent) {
        newNode->next = *start;
        *start = newNode;
        return 1; // success
    }

    // list sorted in descending manner with respect to exponent
    node *temp = *start;
    while (temp->next != NULL && temp->next->exponent > newNode->exponent) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return 1;
}

void displayPolynomial(node *start) {
    if (start == NULL)
        return;

    node *temp = start;
    while (temp != NULL) {
        printf("+%dx^%d", temp->coefficient, temp->exponent);
        temp = temp->next;
    }
    printf("\n");
}

int addPolynomials(node *start1, node *start2, node **result) {
    if (result == NULL)
        return 0; // address of head is null, invalid list
    if (start1 == NULL && start2 == NULL) {
        *result = NULL; // adding two null lists creates a null list
        return 1;
    }

    *result = NULL;

    if (start1->exponent > start2->exponent) {
        *result = start1; // first element of list
        start1 = start1->next;
    } else if (start1->exponent < start2->exponent) {
        *result = start2; // first element of list
        start2 = start2->next;
    } else {
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL)
            return 0;

        newNode->exponent = start1->exponent;
        newNode->coefficient = start1->coefficient + start2->coefficient;

        start1 = start1->next;
        start2 = start2->next;

        *result = newNode; // first term is sum of two terms with same exponent
    }

    node *traverse = *result;

    while (start1 != NULL && start2 != NULL) {
        if (start1->exponent > start2->exponent) {
            traverse->next = start1;
            start1 = start1->next;
        } else if (start1->exponent < start2->exponent) {
            traverse->next = start2;
            start2 = start2->next;
        } else {
            node *newNode = (node *)malloc(sizeof(node));
            if (newNode == NULL)
                return 0;

            newNode->exponent = start1->exponent;
            newNode->coefficient = start1->coefficient + start2->coefficient;
            traverse->next = newNode;
            start1 = start1->next;
            start2 = start2->next;
        }
        traverse = traverse->next;
    }

    if (start1 != NULL) {
        while (start1 != NULL) {
            traverse->next = start1;
            start1 = start1->next;
            traverse = traverse->next;
        }
    } else {
        while (start2 != NULL) {
            traverse->next = start2;
            start2 = start2->next;
            traverse = traverse->next;
        }
    }

    return 1;
}
int main() {
    node *polynomial1 = NULL;
    node *polynomial2 = NULL;
    node *result = NULL;

    insertNode(&polynomial1, 1, 0);
    insertNode(&polynomial1, 1, 1);
    insertNode(&polynomial1, 1, 2);
    printf("Polynomial 1 : \n");
    displayPolynomial(polynomial1);

    insertNode(&polynomial2, 1, 1);
    insertNode(&polynomial2, 1, 2);
    insertNode(&polynomial2, 1, 3);

    printf("Polynomial 2 : \n");
    displayPolynomial(polynomial2);

    addPolynomials(polynomial1, polynomial2, &result);

    printf("Sum of both polynomials : \n");
    displayPolynomial(result);
	return 0;
}
