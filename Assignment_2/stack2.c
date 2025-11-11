#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

int main(){
	int n = 0, m = 0;
	int element = 0;
	stack stack1, stack2;
	int operationFlag = -1;
	printf("Enter size of stack 1 : ");
	scanf("%d", &n);
	printf("Enter size of stack 2 : ");
	scanf("%d", &m);
	operationFlag = initialize(&stack1, n);
	if(0 == operationFlag)
		printf("Could not initialize stack 1\n");
	else
		printf("Initialized stack 1\n");
	operationFlag = initialize(&stack2, m);
	if(0 == operationFlag)
		printf("Could not initialize stack 2\n");
	else
		printf("Initialized stack 2\n");
	while(isFull(&stack1, n) != 1) {
		printf("Push element to stack 1 : ");
		scanf("%d", &element);
		operationFlag = push(&stack1, element, n);
		if(0 == operationFlag)
			printf("Could not push %d\n", element);
	}

	while(isFull(&stack2, m) != 1) {
		printf("Push element to stack 2 : ");
		scanf("%d", &element);
		operationFlag = push(&stack2, element, m);
		if(0 == operationFlag)
			printf("Could not push %d\n", element);
	}
	printf("Now popping all elements from stack 2, then stack 1 : \n");
	printf("Popping from stack 2 : ");
	while(isEmpty(&stack2) != 1) {
		operationFlag = pop(&stack2, &element);
		if(0 == operationFlag)
			printf("Could not pop element !");
		else
			printf(" %d", element);
	}
	printf("\nPopping from stack 1 : ");
	while(isEmpty(&stack1) != 1) {
		operationFlag = pop(&stack1, &element);
		if(0 == operationFlag)
			printf("Could not pop element !");
		else
			printf(" %d", element);
	}
	printf("\n");
	freeStack(&stack1);
	freeStack(&stack2);
	return 0;
	
}
