#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ll long long

typedef struct {
    ll comparisons;
    int maxDepth;
} sortMetrics;

void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *a, int low, int high, sortMetrics *metrics) {
    int pivot_index = low + rand() % (high - low + 1);
    swap(&a[pivot_index], &a[high]);

    int i = low - 1;
    int pivot = a[high];

    for (int j = low; j < high; j++) {
        metrics->comparisons++;
        if (a[j] <= pivot) {
            swap(&a[++i], &a[j]);
        }
    }
    swap(&a[++i], &a[high]);
    return i;
}

void quickSort(int *a, int low, int high, int currentDepth,
               sortMetrics *metrics) {
    if (low < high) {
        if (currentDepth > metrics->maxDepth) {
            metrics->maxDepth = currentDepth;
        }

        int partition_index = partition(a, low, high, metrics);
        quickSort(a, low, partition_index - 1, currentDepth + 1, metrics);
        quickSort(a, partition_index + 1, high, currentDepth + 1, metrics);
    }
}

void merge(int *leftArray, int leftSize, int *rightArray, int rightSize,
           int *array, sortMetrics *metrics) {
    int i = 0, l = 0, r = 0;
    while (l < leftSize && r < rightSize) {
        metrics->comparisons++;
        if (leftArray[l] < rightArray[r])
            array[i++] = leftArray[l++];
        else
            array[i++] = rightArray[r++];
    }
    while (l < leftSize)
        array[i++] = leftArray[l++];
    while (r < rightSize)
        array[i++] = rightArray[r++];
}

void mergeSort(int *array, int n, int currentDepth, sortMetrics *metrics) {
    if (n <= 1)
        return;

    if (currentDepth > metrics->maxDepth) {
        metrics->maxDepth = currentDepth;
    }

    int mid = n / 2;
    int leftSize = mid;
    int rightSize = n - mid;

    int *leftArray = (int *)malloc(leftSize * sizeof(int));
    int *rightArray = (int *)malloc(rightSize * sizeof(int));

    if (leftArray == NULL || rightArray == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    memcpy(leftArray, array, leftSize * sizeof(int));
    memcpy(rightArray, &array[mid], rightSize * sizeof(int));

    mergeSort(leftArray, leftSize, currentDepth + 1, metrics);
    mergeSort(rightArray, rightSize, currentDepth + 1, metrics);
    merge(leftArray, leftSize, rightArray, rightSize, array, metrics);

    free(leftArray);
    free(rightArray);
}

void generateData(int *a, int n) {
    int sorted = n * 0.8;
    // 80% of data is sorted
    for (int i = 0; i < sorted; i++) {
        a[i] = i;
    }

    // From that 80%, 5% of it is randomized/unsorted
    for (int i = 0; i < sorted / 20; i++) {
        int i1 = rand() % sorted;
        int i2 = rand() % sorted;
        swap(&a[i1], &a[i2]);
    }

    // rest of it is unsorted
    for (int i = sorted; i < n; i++) {
        a[i] = rand() % n;
    }
}

int main() {
    int n = (int)1e5;
    srand(time(NULL));

    int *arrayQuickSort = (int *)malloc(n * sizeof(int));
    int *arrayMergeSort = (int *)malloc(n * sizeof(int));

    if (!arrayMergeSort || !arrayQuickSort) {
        printf("Memory allocation failed\n");
        return -1;
    }

    printf("Generating array : %d elements (80%% nearly sorted)\n", n);
    generateData(arrayQuickSort, n);
    memcpy(arrayMergeSort, arrayQuickSort, n * sizeof(int));
    printf("Generated array!\n");

    sortMetrics quickSortMetrics = {0, 0};
    printf("\nRunning Quick Sort (randomized pivot)\n");

    clock_t start = clock();
    quickSort(arrayQuickSort, 0, n - 1, 0, &quickSortMetrics);
    clock_t end = clock();

    double quickSortTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("  Execution Time      : %.f seconds\n", quickSortTime);
    printf("  Key Comparisons     : %lld\n", quickSortMetrics.comparisons);
    printf("  Max Recursion Depth : %d\n", quickSortMetrics.maxDepth);

    sortMetrics mergeSortMetrics = {0, 0};

    printf("\nRunning Merge Sort\n");

    start = clock();
    mergeSort(arrayMergeSort, n, 0, &mergeSortMetrics);
    end = clock();

    double mergeSortTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("  Execution Time      : %.f seconds\n", mergeSortTime);
    printf("  Key Comparisons     : %lld\n", mergeSortMetrics.comparisons);
    printf("  Max Recursion Depth : %d\n", mergeSortMetrics.maxDepth);

    free(arrayMergeSort);
    free(arrayQuickSort);

    return 0;
}
