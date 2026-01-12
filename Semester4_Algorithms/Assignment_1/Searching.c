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

int partition(int *a, int low, int high) {
    int mid = (high + low) >> 1;
    if (a[low] > a[mid]) {
        swap(&a[low], &a[mid]);
    }
    if (a[low] > a[high]) {
        swap(&a[low], &a[high]);
    }
    if (a[mid] > a[high]) {
        swap(&a[mid], &a[high]);
    }
    // now we have sorted the three elements at these positions, so our median
    // would be a[mid] we put a[mid] at high for the algorithm and choosing this
    // as pivot
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

int main() {
    // variable declaration zone
    int mid = 0;
    int left = 0;
    int n = 50000;
    int right = n - 1;
    int target = 0;
    int index = -1;
    clock_t start, end;
    int comparisons_linear = 0;
    int comparisons_binary = 0;
    int array[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }
    printf("Array with 50k elements created!\n");
    printf("\n");
    printf("Enter target element: ");
    scanf("%d", &target);
    printf("Performing linear search!\n");
    start = clock();
    for (int i = 0; i < n; i++) {
        comparisons_linear++;
        if (array[i] == target) {
            index = i;
            break;
        }
    }
    end = clock();
    if (index == -1) {
        printf("Could not find target %d\n", target);
    } else {
        printf("Target element found at position %d\n", index);
    }
    printf("Number of comparisons : %d\n", comparisons_linear);
    printf("Time taken: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("Performing binary search!\n");
    printf("First sorting the array!\n");
    start = clock();
    quickSort(array, 0, n - 1);
    end = clock();
    printf("Sorted the array!\n");
    printf("Time taken to sort array : %f\n",
           (double)(end - start) / CLOCKS_PER_SEC);
    index = -1;
    start = clock();
    while (left <= right) {
        mid = (left + right) >> 1;
        if (target < array[mid]) {
            comparisons_binary++;
            right = mid - 1;
        } else if (target > array[mid]) {
            comparisons_binary++;
            left = mid + 1;
        } else {
            index = mid;
            break;
        }
    }
    end = clock();
    if (index == -1) {
        printf("Could not find target %d!\n", target);
    } else {
        printf("Found target at position %d\n", index);
    }
    printf("Number of comparisons : %d\n", comparisons_binary);
    printf("Time taken: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
