#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(int a[], int n) {
    if (a == NULL)
        return;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

void InsertionSort(int *a, int n) {
    if (a == NULL)
        return;
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int partition(int *a, int low, int high) {
    int mid = (high + low) >> 1;
    if (a[low] > a[mid])
        swap(&a[low], &a[mid]);
    if (a[low] > a[high])
        swap(&a[low], &a[high]);
    if (a[mid] > a[high])
        swap(&a[mid], &a[high]);

    swap(&a[mid], &a[high]);

    int i = low - 1;
    int pivot = a[high];

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            swap(&a[++i], &a[j]);
        }
    }
    swap(&a[++i], &a[high]);
    return i;
}

void quickSort(int *a, int low, int high) {
    if (low < high) {
        int partition_index = partition(a, low, high);
        quickSort(a, low, partition_index - 1);
        quickSort(a, partition_index + 1, high);
    }
}

void merge(int *leftArray, int leftSize, int *rightArray, int rightSize,
           int *array) {
    int i = 0, l = 0, r = 0;
    while (l < leftSize && r < rightSize) {
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

void mergeSort(int *array, int n) {
    if (n <= 1)
        return;
    int mid = n / 2;
    int leftSize = mid;
    int rightSize = n - mid;

    int *leftArray = (int *)malloc(leftSize * sizeof(int));
    int *rightArray = (int *)malloc(rightSize * sizeof(int));

    memcpy(leftArray, array, leftSize * sizeof(int));
    memcpy(rightArray, &array[mid], rightSize * sizeof(int));

    mergeSort(leftArray, leftSize);
    mergeSort(rightArray, rightSize);
    merge(leftArray, leftSize, rightArray, rightSize, array);

    free(leftArray);
    free(rightArray);
}

void showStats(int n) {

    int *master = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        master[i] = rand();
    }

    clock_t start, end;
    double time_taken;

    printf("| %-10d | ", n);

    memcpy(temp, master, n * sizeof(int)); // Reset array
    start = clock();
    BubbleSort(temp, n);
    end = clock();
    printf("%-10f | ", ((double)(end - start)) / CLOCKS_PER_SEC);

    memcpy(temp, master, n * sizeof(int)); // Reset array
    start = clock();
    InsertionSort(temp, n);
    end = clock();
    printf("%-10f | ", ((double)(end - start)) / CLOCKS_PER_SEC);

    memcpy(temp, master, n * sizeof(int)); // Reset array
    start = clock();
    quickSort(temp, 0, n - 1);
    end = clock();
    printf("%-10f | ", ((double)(end - start)) / CLOCKS_PER_SEC);

    memcpy(temp, master, n * sizeof(int)); // Reset array
    start = clock();
    mergeSort(temp, n);
    end = clock();
    printf("%-10f |\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    free(master);
    free(temp);
}

int main() {
    srand(time(NULL));

    printf("Performance Comparison (Time in seconds)\n");
    printf("-------------------------------------------------------------------"
           "---------------\n");
    printf("| %-10s | %-10s | %-10s | %-10s | %-10s |\n", "Size", "Bubble",
           "Insertion", "Quick", "Merge");
    printf("-------------------------------------------------------------------"
           "---------------\n");

    int sizes[] = {5000,  10000, 15000, 20000, 25000,
                   30000, 35000, 40000, 45000, 50000};
    int num_sizes = 10;

    for (int i = 0; i < num_sizes; i++) {
        showStats(sizes[i]);
    }

    printf("-------------------------------------------------------------------"
           "---------------\n");
    return 0;
}
