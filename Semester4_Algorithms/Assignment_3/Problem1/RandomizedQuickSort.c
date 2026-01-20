#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *a, int low, int high, int *comparisons) {
    int pivot_index = low + (rand() % (high - low + 1));
    int i = low - 1;
    int pivot = a[pivot_index];
    swap(&a[pivot_index], &a[high]);

    for (int j = low; j < high; j++) {
        (*comparisons)++;
        if (a[j] <= pivot) {
            swap(&a[++i], &a[j]);
        }
    }
    swap(&a[++i], &a[high]);
    return i;
}

void quickSort(int *a, int low, int high, int *comparisons) {
    if (low < high) {
        int partition_index = partition(a, low, high, comparisons);
        quickSort(a, low, partition_index - 1, comparisons);
        quickSort(a, partition_index + 1, high, comparisons);
    }
}

void printArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

bool isSorted(int *a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i])
            return false;
    }
    return true;
}

int main() {
    srand(time(NULL));
    int comparisons = 0;
    clock_t start, end;

    int n = (int)1e5;

    int a[n];

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 101;
    }

    if (isSorted(a, n)) {
        printf("Array is already sorted!\n");
        return 1;
    }
    printf("Array has been succesfully populated!\n");
    printf("First 10 elements of array: \n");
    printArray(a, 10);

    printf("Sorting array!\n");
    start = clock();
    quickSort(a, 0, n - 1, &comparisons);
    end = clock();
    printf("Done sorting!\n");

    printf("First 10 elements of array after sorting : \n");
    printArray(a, 10);

    printf("Time taken : %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Number of comparisons : %d", comparisons);

    return 0;
}
