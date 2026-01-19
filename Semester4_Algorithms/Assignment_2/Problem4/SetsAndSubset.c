#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool binarySearch(int *a, int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) >> 1;

        if (a[mid] == target)
            return true;
        if (a[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false;
}

void insertSorted(int *a, int *currentSize, int value) {
    int i = *currentSize - 1;

    while (i >= 0 && a[i] > value) {
        a[i + 1] = a[i];
        i--;
    }

    a[i + 1] = value;
    (*currentSize)++;
}

void fillSet(int *a, int n, char name) {
    int input;
    int count = 0;

    printf("Enter %d distinct integers for set %c: ", n, name);

    while (count < n) {
        printf("Element %d : ", count + 1);
        scanf("%d", &input);

        if (count > 0 && binarySearch(a, count, input)) {
            printf("[ERROR] Duplicate! Try again.\n");
        } else
            insertSorted(a, &count, input);
    }

    printf("\n");
}

bool checkSubset(int *setA, int nA, int *setB, int nB) {
    if (nA > nB)
        return false;

    int i = 0, j = 0;

    while (i < nA && j < nB) {
        if (setA[i] < setB[j]) {
            return false;
        } else if (setA[i] == setB[j]) {
            i++;
            j++;
        } else
            j++;
    }

    return (i == nA);
}

int main() {
    int nA, nB;

    printf("Enter size for setA : ");
    scanf("%d", &nA);
    printf("Enter size for Set B: ");
    scanf("%d", &nB);
    printf("\n");

    int *setA = (int *)malloc(nA * sizeof(int));
    int *setB = (int *)malloc(nB * sizeof(int));

    fillSet(setA, nA, 'A');
    fillSet(setB, nB, 'B');

    printf("Set A (Sorted): { ");
    for (int i = 0; i < nA; i++)
        printf("%d ", setA[i]);
    printf("}\n");

    printf("Set B (Sorted): { ");
    for (int i = 0; i < nB; i++)
        printf("%d ", setB[i]);
    printf("}\n\n");

    bool isSubset = checkSubset(setA, nA, setB, nB);
    bool isProperSubset = isSubset && (nA < nB);

    printf("---------------- RESULTS ----------------\n");
    if (isSubset) {
        printf("Set A is a SUBSET of Set B.\n");
        if (isProperSubset)
            printf("Set A is a PROPER SUBSET.\n");
        else
            printf("Set A is NOT a proper subset (Identical sets).\n");
    } else {
        printf("Set A is NOT a subset of Set B.\n");
    }
    printf("-----------------------------------------\n");

    free(setA);
    free(setB);
    return 0;
}
