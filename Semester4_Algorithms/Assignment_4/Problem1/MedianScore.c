#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *a, int low, int high) {
    int pivot_index = high;
    int i = low - 1;
    int pivot = a[pivot_index];
    swap(&a[pivot_index], &a[high]);

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            swap(&a[++i], &a[j]);
        }
    }
    swap(&a[++i], &a[high]);
    return i;
}

int fixedPivotMedian(int *a, int low, int high, const int medianIndex) {
	if(low <= high) {
		int partitionIndex = partition(a, low, high);
		if(partitionIndex == medianIndex) {
			return a[partitionIndex];
		}
		if(partitionIndex > medianIndex) return fixedPivotMedian(a, low, partitionIndex - 1, medianIndex);
		else if(partitionIndex < medianIndex) return fixedPivotMedian(a, partitionIndex + 1, high, medianIndex);
	}
	return -1;
}	

int quickSelect(int *a, int low, int high , int kthSmallestElement) {
	if(kthSmallestElement > 0 && kthSmallestElement <= high - low + 1) {
		int index = partition(a, low, high);
		if(index - low == kthSmallestElement - 1) return a[index];

		if(index - low > kthSmallestElement - 1) return quickSelect(a, low, index - 1, kthSmallestElement);
		else return quickSelect(a, index + 1, high, kthSmallestElement - (index - low + 1));
	}
	return -1;
}

int main() {
	int n = (int) 1e5 + 1e4;
	int medianIndex = -1;
	clock_t start, end;
	int *a = (int *) malloc(n * sizeof(int));
	srand(time(NULL));
	for(int i = 0; i < n; i++) a[i] = rand() % 100;

	printf("First 10 elements of the array : \n");
	for(int i = 0; i < 10; i++) printf("%d ", a[i]);
	printf("\n");

	printf("Finding median using fixed pivot\n");
	start = clock();
	medianIndex = fixedPivotMedian(a, 0, n - 1, n / 2 + 1);
	end = clock();
	printf("Time taken : %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("Median = %d\n", a[medianIndex]);

	printf("Finding median using quick Select algorithm\n");

	start = clock();
	medianIndex = quickSelect(a, 0, n - 1, n / 2 + 1);
	end = clock();

	printf("Time taken : %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	printf("Median = %d\n", a[medianIndex]);
	return 0;

}
