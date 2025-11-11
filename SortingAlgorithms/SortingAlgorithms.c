#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printList(int list[], int n) {
    if (list == NULL) {
        return;
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printExchangesAndList(int *a, int n, int number_of_exchanges) {
    printf("\n");
    printf("Number of exchanges = %d\n", number_of_exchanges);
    printf("List after soring : ");
    printList(a, n);
    printf("\n");
}

int findMaxPosInSubArray(int *a, int start, int end) {
    int max_pos = start;

    for (int i = start + 1; i <= end; i++) {
        if (a[i] > a[max_pos]) {
            max_pos = i;
        }
    }
    return max_pos;
}

int findMinPosInSubArray(int *a, int start, int end) {
    int min_pos = start;

    for (int i = start + 1; i <= end; i++) {
        if (a[i] < a[min_pos]) {
            min_pos = i;
        }
    }
    return min_pos;
}

// case 1
void InsertionSort(int *a, int n) {
    int number_of_exchanges = 0;

    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (a[j - 1] > a[j]) {
                swap(&a[j - 1], &a[j]);
                number_of_exchanges++;
            } else {
                break;
            }
        }
    }
    printExchangesAndList(a, n, number_of_exchanges);
}

// case 2
void InsertionSortAvoidSwap(int *a, int n) {
    if (a == NULL) {
        return;
    }
    printf("\n");
    printf("List before sorting : ");
    printList(a, n);
    int i, key, j, number_of_exchanges = 0;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
        number_of_exchanges++;
    }
    printExchangesAndList(a, n, number_of_exchanges);
}

// case 3
void BubbleSort(int a[], int n) {
    if (a == NULL) {
        return;
    }
    printf("\nList before sorting : ");
    printList(a, n);
    int number_of_exchanges = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                number_of_exchanges++;
            }
        }
    }
    printExchangesAndList(a, n, number_of_exchanges);
}

// case 4
void BubbleSortAvoidSwap(int *a, int n) {
    if (a == NULL)
        return;

    int number_of_exchanges = 0;
    printf("List before sorting : ");
    printList(a, n);
    for (int i = n - 1; i > 0; i--) {
        int max = a[0]; // assume a[0] is the max
        for (int j = 1; j <= i; j++) {
            if (a[j] < max) {
                a[j - 1] = a[j]; // move
            } else {
                a[j - 1] = max; // store the old max
                max = a[j];     // get the new max
            }
        }
        a[i] = max; // store the max}
        number_of_exchanges++;
    }

    printExchangesAndList(a, n, number_of_exchanges);
}

// case 5
void BubbleSortFlagged(int *a, int n) {
    int number_of_exchanges = 0;
    printf("List before sorting : ");
    printList(a, n);
    for (int i = n - 1; i > 0; i--) {
        int max = a[0];
        bool sorted = true;
        for (int j = 1; j <= i; j++) {
            if (a[j] < max) {
                a[j - 1] = a[j];
                sorted = false;
            } else {
                a[j - 1] = max;
                max = a[j];
            }
        }
        if (sorted)
            break;
        a[i] = max;
        number_of_exchanges++;
    }
    printExchangesAndList(a, n, number_of_exchanges);
}

// case 6
void BubbleSortRangeLimit(int *a, int n) {
    int number_of_exchanges = 0;
    printf("List before sorting : ");
    printList(a, n);
    for (int i = n - 1; i > 0;) {
        int max = a[0];
        int index = 0;
        for (int j = 1; j <= i; j++) {
            if (a[j] < max) {
                a[j - 1] = a[j];
                index = j - 1;
            } else {
                a[j - 1] = max;
                max = a[j];
            }
        }
        a[i] = max;
        i = index;
        number_of_exchanges++;
    }
    printExchangesAndList(a, n, number_of_exchanges);
}

// case 7
void BubbleSortAlternating(int *a, int n) {
    int start = 0, end = n - 1, number_of_exchanges = 0;

    printf("List before sorting : ");
    printList(a, n);

    while (start < end) {
        int max_pos = findMaxPosInSubArray(a, start, end);
        int min_pos = findMinPosInSubArray(a, start, end);

        if (min_pos != start) {
            swap(&a[start], &a[min_pos]);
            number_of_exchanges++;
        }

        if (max_pos == start) {
            max_pos = min_pos;
        }

        if (max_pos != end) {
            swap(&a[end], &a[max_pos]);
            number_of_exchanges++;
        }

        start++;
        end--;
    }
    printExchangesAndList(a, n, number_of_exchanges);
}

// case 8
void merge(int *leftArray, int leftSize, int *rightArray, int rightSize,
           int *array) {
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        if (leftArray[l] < rightArray[r]) {
            array[i] = leftArray[l];
            i++;
            l++;
        } else {
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }

    while (l < leftSize) {
        array[i] = leftArray[l];
        i++;
        l++;
    }

    while (r < rightSize) {
        array[i] = rightArray[r];
        i++;
        r++;
    }
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

void mergeSortPrint(int *a, int n) {
    printf("List before sorting : ");
    printList(a, n);

    mergeSort(a, n);

    printf("\n");
    printf("List after sorting : ");
    printList(a, n);
    printf("\n");
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

// case 9
void quickSortPrint(int *a, int n) {
    printf("List before sorting : ");
    printList(a, n);

    quickSort(a, 0, n - 1);

    printf("\nList after sorting : ");
    printList(a, n);
    printf("\n");
}

int main() {
    // variable declaration zone

    int n = 20;
    int choice = -1;

    int list1[20] = {1,  16, 12, 26, 25, 35, 33, 58, 45, 42,
                     56, 67, 83, 75, 74, 86, 81, 88, 99, 95};

    int list2[20] = {1,  17, 21, 42, 24, 27, 32, 35, 45, 47,
                     57, 23, 66, 69, 70, 76, 87, 85, 95, 99};

    int list3[20] = {22, 20, 81, 38, 95, 84, 99, 12, 79, 44,
                     26, 87, 96, 10, 48, 80, 1,  31, 16, 92};

    int tempList[n];

    do {
        printf("Enter your choice : \n"
               "1. InserionSort\n"
               "2. InsertionSort avoiding swaps\n"
               "3. BubbleSort\n"
               "4. BubbleSort avoiding swaps\n"
               "5. Flagged BubbleSort\n"
               "6. Range limiting BubbleSort\n"
               "7. Alternating BubbleSort\n"
               "8. Merge Sort\n"
               "9. Quick sort (using pivot selection by median of three)\n"
               "0. EXIT\n");

        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Exiting program...\n");
            break;
        case 1:
            memcpy(tempList, list1, n * sizeof(int));
            InsertionSort(tempList, 20);
            memcpy(tempList, list2, n * sizeof(int));
            InsertionSort(tempList, 20);
            memcpy(tempList, list3, n * sizeof(int));
            InsertionSort(tempList, 20);
            break;
        case 2:
            memcpy(tempList, list1, n * sizeof(int));
            InsertionSortAvoidSwap(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            InsertionSortAvoidSwap(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            InsertionSortAvoidSwap(tempList, n);
            break;
        case 3:
            memcpy(tempList, list1, n * (sizeof(int)));
            BubbleSort(tempList, 20);
            memcpy(tempList, list2, n * (sizeof(int)));
            BubbleSort(tempList, 20);
            memcpy(tempList, list3, n * sizeof(int));
            BubbleSort(tempList, 20);
            break;
        case 4:
            memcpy(tempList, list1, n * sizeof(int));
            BubbleSortAvoidSwap(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            BubbleSortAvoidSwap(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            BubbleSortAvoidSwap(tempList, n);
            break;
        case 5:
            memcpy(tempList, list1, n * sizeof(int));
            BubbleSortFlagged(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            BubbleSortFlagged(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            BubbleSortFlagged(tempList, n);
            break;
        case 6:
            memcpy(tempList, list1, n * sizeof(int));
            BubbleSortRangeLimit(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            BubbleSortRangeLimit(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            BubbleSortRangeLimit(tempList, n);
            break;
        case 7:
            memcpy(tempList, list1, n * sizeof(int));
            BubbleSortAlternating(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            BubbleSortAlternating(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            BubbleSortAlternating(tempList, n);
            break;
        case 8:
            memcpy(tempList, list1, n * sizeof(int));
            mergeSortPrint(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            mergeSortPrint(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            mergeSortPrint(tempList, n);
            break;
        case 9:
            memcpy(tempList, list1, n * sizeof(int));
            quickSortPrint(tempList, n);
            memcpy(tempList, list2, n * sizeof(int));
            quickSortPrint(tempList, n);
            memcpy(tempList, list3, n * sizeof(int));
            quickSortPrint(tempList, n);
            break;
        default:
            printf("Wrong choice\n");
        }

    } while (choice != 0);

    return 0;
}
