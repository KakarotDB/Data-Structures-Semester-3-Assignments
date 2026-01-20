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

int RandomPartition(int *a, int low, int high, int *comparisons) {
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

void RandomQuickSort(int *a, int low, int high, int *comparisons) {
    if (low < high) {
        int partition_index = RandomPartition(a, low, high, comparisons);
        RandomQuickSort(a, low, partition_index - 1, comparisons);
        RandomQuickSort(a, partition_index + 1, high, comparisons);
    }
}

int StandardPartition(int *a, int low, int high, int *comparisons) {
    int pivot_index = high;
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

void StandardQuickSort(int *a, int low, int high, int *comparisons) {
    if (low < high) {
        int partition_index = RandomPartition(a, low, high, comparisons);
        StandardQuickSort(a, low, partition_index - 1, comparisons);
        StandardQuickSort(a, partition_index + 1, high, comparisons);
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
    int n = (int)1e5;
    srand(time(NULL));

    int a1[n], a2[n], a3[n];

    // a1 will have 90% duplicates -> 90k elements will be the same
    // a2 will have 50% duplicates -> 50k elements will be the same
    // a3 will have 10% duplicates -> 10k elements will be the same

    for (int i = 0; i < 90000; i++) {
        a1[i] = 1;
    }
    for (int i = 90000; i < n; i++) {
        a1[i] = rand();
    }

    for (int i = 0; i < 50000; i++) {
        a2[i] = 1;
    }
    for (int i = 50000; i < n; i++) {
        a2[i] = rand();
    }

    for (int i = 0; i < 10000; i++) {
        a3[i] = 1;
    }
    for (int i = 10000; i < n; i++) {
        a3[i] = rand();
    }
}
