#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void ThirdSmallest(int *a, int n) {
	int s1, s2, s3;
	s1 = s2 = s3 = INT_MAX;

	for(int i = 0; i < n; i++) {
		int val = a[i];
		if(val < s1) {
			s3 = s2; s2 = s1; s1 = val;
		}
		else if(val < s2 && val != s1) {
			s3 = s2; s2 = val;
		}
		else if(val < s3 && val != s1 && val != s2){
			s3 = val;
		}
	}

	printf("Third smallest integer in the array is : %d\n", s3);
}
	
void FourthLargest(int *a, int n) {
	int l1, l2, l3, l4;
	l1 = l2 = l3 = l4 = INT_MIN;

	for(int i = 0; i < n; i++) {
		int val = a[i];

		if(val > l1) {
			l4 = l3, l3 = l2, l2 = l1, l1 = val;
		}
		else if(val > l2 && val != l1) {
			l4 = l3, l3 = l2, l2 = val;
		} 
		else if(val > l3 && val != l1 && val != l2) {
			l4 = l3, l3 = val;
		}
		else if(val > l4 && val != l1 && val != l2 && val != l3) {
			l4 = val;
		}
	}

	printf("Fourth largest integer in the array is : %d\n", l4);
}
void printArray(int *a, int n) {
	for(int i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\n");
}

int main() {
	//variable declaration zone
	int n = 0;
	int *a = NULL;
	printf("Enter value of n (n >= 10) : \n");
	scanf("%d", &n);
	if(n < 10) {
		printf("n is lesser than 10, program exiting\n");
		return -1;	
	}

	srand(time(NULL)); 

	a = (int *) malloc(n * sizeof(int));
	if(a == NULL) {
		printf("Memory allocation failed!\n");
		return -1;
	}

	for(int i = 0; i < n; i++) a[i] = rand() % 10;

	ThirdSmallest(a, n);
	FourthLargest(a, n);

	printf("Array elements are : \n");
	printArray(a, n);
}
