#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {
    int k;
    int *masterArray = NULL; // holding all elements from all arrays
    int totalElements = 0;

    printf("Enter number of sets: ");
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int n;
        printf("\nEnter number of elements in Set %d: ", i + 1);
        scanf("%d", &n);

        int *temp = realloc(masterArray, (totalElements + n) * sizeof(int));

        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return -1;
        }

        masterArray = temp;

        printf("Enter %d integers for Set %d: ", n, i + 1);

        for (int j = 0; j < n; j++) {
            scanf("%d", &masterArray[totalElements + j]);
        }

        totalElements += n;
    }

    qsort(masterArray, totalElements, sizeof(int), compare);

    printf("Union of all sets: ");

    if (totalElements > 0) {
        printf("%d", masterArray[0]);

        for (int i = 1; i < totalElements; i++) {
            if (masterArray[i] != masterArray[i - 1]) {
                printf(", %d", masterArray[i]);
            }
        }
    }

    free(masterArray);
}
