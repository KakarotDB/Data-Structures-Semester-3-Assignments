#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
	int max; 
	int min; 
	int count;
} Result;

//functions returns number of comparisons
int naiveMaxMin(int *a, int n) {
	int max = a[0];
	int min = a[0];
	int comparisons = 0;

	for(int i = 1; i < n; i++) {
		int val = a[i];

		max = val >= max ? val : max;
		min = val <= min ? val : min;

		comparisons+=2;
	}

	//printf("Max : %d\n", max);
	//printf("Min : %d\n", min);
	return comparisons;
}

Result recursiveMaxMin(int *a, int low, int high) {
	Result result, left, right;
	int mid;

	if(low == high) { //1 element
		result.max = a[0];
		result.min = a[0];
		result.count = 0;
		return result;
	}

	if(high == low + 1) { //2 elements
		if(a[low] > a[high]) {
			result.max = a[low];
			result.min = a[high];
			result.count = 1;
			return result;
		} else {
			result.max = a[high];
			result.min = a[low];
			result.count = 1;
			return result;
		}
	}

	mid = (low + high) >> 1;
	left = recursiveMaxMin(a, low, mid);
	right = recursiveMaxMin(a, mid + 1, high);

	result.max = left.max > right.max ? left.max : right.max;
	result.min = left.min < right.min ? left.min : right.min;
	result.count = left.count + right.count + 2;

	return result;
}
void insertSizes(int *a) {
	int i = 0;
	for(;i < 3; i++) a[i] = pow(10, i + 2);
	for(;i < 12; i++) a[i] = a[i - 1] + 10000;
}

void populateArray(int *a, int n) {
	for(int i = 0; i < n; i++) a[i] = rand();
}

void printArray(int *a, int n) {
	for(int i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\n");
}


int main() {
	int n = 12;
	int sizes[n];
	Result result;

	insertSizes(sizes); //Sizes are 100, 1000, 10000, 20000, .... , 100,000
	
	sizes[1] = 1024;
	printf("| %-10s | %-25s | %-15s\n", "Size", "Naive MaxMin(Comparisons)", "Recursive MaxMin(Comparisons)");
	printf("----------------------------------------------------------------------\n");

	for(int i = 0; i < n; i++) {
		int *a = (int *) malloc(sizes[i] * sizeof(int));
		if(a == NULL) {
			printf("Memory allocation failed!\n");
			return -1;
		}

		populateArray(a, sizes[i]);
		result = recursiveMaxMin(a, 0, sizes[i] - 1);
		printf("| %-10d | %-25d | %-15d\n", sizes[i], naiveMaxMin(a, sizes[i]), result.count);

		free(a);
	}
	
	printf("----------------------------------------------------------------------\n");
	return 0;
}
