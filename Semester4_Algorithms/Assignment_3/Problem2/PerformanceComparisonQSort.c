#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ll long long

typedef struct {
    ll comparisons;
    int max_depth;
    double time_taken;
} SortStats;

void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleArray(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&a[i], &a[j]);
    }
};

int StandardPartition(int *a, int low, int high, ll *comparisons) {
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

int RandomPartition(int *a, int low, int high, ll *comparisons) {
    int pivot_index = low + (rand() % (high - low + 1));
    swap(&a[pivot_index], &a[high]);
    return StandardPartition(a, low, high, comparisons);
}

void RandomQuickSort(int *a, int low, int high, SortStats *stats,
                     int currentDepth) {
    if (currentDepth > stats->max_depth) {
        stats->max_depth = currentDepth;
    }
    if (low < high) {
        int partition_index =
            RandomPartition(a, low, high, &stats->comparisons);
        RandomQuickSort(a, low, partition_index - 1, stats, currentDepth + 1);
        RandomQuickSort(a, partition_index + 1, high, stats, currentDepth + 1);
    }
}

void StandardQuickSort(int *a, int low, int high, SortStats *stats,
                       int currentDepth) {
    if (currentDepth > stats->max_depth) {
        stats->max_depth = currentDepth;
    }
    if (low < high) {
        int partition_index =
            StandardPartition(a, low, high, &stats->comparisons);
        StandardQuickSort(a, low, partition_index - 1, stats, currentDepth + 1);
        StandardQuickSort(a, partition_index + 1, high, stats,
                          currentDepth + 1);
    }
}

SortStats runStandardSort(int *a, int n) {
    SortStats s = {0, 0, 0.0};
    clock_t start = clock();
    StandardQuickSort(a, 0, n - 1, &s, 0);
    clock_t end = clock();
    s.time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    return s;
}

SortStats runRandomSort(int *a, int n) {
    SortStats s = {0, 0, 0.0};
    clock_t start = clock();
    RandomQuickSort(a, 0, n - 1, &s, 0);
    clock_t end = clock();
    s.time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    return s;
}

void printArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void analyze(char *name, int percent_duplicates, int n) {
    printf("--- Analyzing %s (%d%% Duplicates) ---\n", name,
           percent_duplicates);
    int *original_data = (int *)malloc(n * sizeof(int));
    int duplicate_count = (n * percent_duplicates) / 100;
    int unique_count = n - duplicate_count;

    for (int i = 0; i < duplicate_count; i++)
        original_data[i] = 1;
    for (int i = duplicate_count; i < n; i++)
        original_data[i] = rand();

    shuffleArray(original_data, n);

    int *arr_std = (int *)malloc(n * sizeof(int));
    int *arr_rnd = (int *)malloc(n * sizeof(int));

    memcpy(arr_std, original_data, n * sizeof(int));
    memcpy(arr_rnd, original_data, n * sizeof(int));

    SortStats standard = runStandardSort(arr_std, n);
    printf("[Standard QS]   Time: %.4fs | Comparisons: %llu | Max Depth: %d\n",
           standard.time_taken, standard.comparisons, standard.max_depth);

    SortStats random = runRandomSort(arr_rnd, n);
    printf(
        "[Randomized QS] Time: %.4fs | Comparisons : %llu | Max depth : %d\n",
        random.time_taken, random.comparisons, random.max_depth);
    printf("\n");

    free(original_data);
    free(arr_rnd);
    free(arr_std);
}

int main() {
    int n = (int)1e4;
    srand(time(NULL));

    printf("Running analysis on array size %d\n", n);

    // 90% Duplicates
    analyze("Array I", 90, n);

    // 50% Duplicates
    analyze("Array II", 50, n);

    // 10% Duplicates
    analyze("Array III", 10, n);

    return 0;
}
