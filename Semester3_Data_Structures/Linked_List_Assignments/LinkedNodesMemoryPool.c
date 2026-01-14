#include <stdio.h>
#include <stdlib.h>
#define N 100;

typedef struct node {
	int data;
	struct node* next;
} node;

int createMemoryPoolNodes(node** start) { //this method will create up-to 100 nodes 
	if(start == NULL) {
		return 0; //invalid list
	}
	
	*start = NULL;

	node* newNode = (node*) (malloc(sizeof(node)));

	if(newNode == NULL)
		return 0; //memory allocation failed

	newNode->next = newNode;
	newNode->data = 0; //initialized data

	*start = newNode;
   	int i = 1; 
    for(i = 1; i < 100; i++) {
		node* newNode = (node*) malloc(sizeof(node));

		if(newNode == NULL){
			return 0; //memory allocation failed
			break;
		}
		newNode->next = (*start)->next;
		newNode->data = 0; //all values initialized to 0, can be changed later
		(*start)->next = newNode;
	}
	return 1;
}

int releaseMemoryNodes(node** start, int* log) {
	if(start == NULL || log == NULL || *start == NULL)
		return 0;
	
	node* temp = *start;

	int count = 0;

	while(temp->next != temp) {
		node* previous = temp;
		temp = temp->next;
		free(previous);
		count++;
	}

	free(temp);
	count++;

	*log = N - count;
	return 1;
}

int main() {
	node* memoryPool = NULL;

	if(createMemoryPoolNodes(&memoryPool) == 1){
		printf("Successfully created memory pool of nodes with 100 nodes !\n");
	}
	else {
		printf("Failed at creating memory pool! Program will exit now.\n");
		return -1;
	}
}
