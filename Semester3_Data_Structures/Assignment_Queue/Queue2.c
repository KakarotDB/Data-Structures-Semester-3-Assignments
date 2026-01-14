#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	srand(time(NULL));
	Queue *q = NULL;
	int n = 0;
	int qElement = 0;
	int operationFlag = -1;
	int rValue = rand() % 10 + 1;
	printf("The random value rValue is %d\n", rValue);
	printf("Enter size of queue : ");
	scanf("%d", &n);
	q = createQ(n);
	if(q == NULL)
		printf("Unable to initialize queue!\n");
	else
		printf("Queue successfully initialized with zero initialization with size %d!\n", (n - 1));
	printf("Enter %d elements into queue, one by one : \n", (n - 1));
	for(int i = 0; i < n - 1; i++){
		scanf("%d", &qElement);
		operationFlag = enqueue(q, qElement, n);		
		if(0 == operationFlag) {
			printf("Failed to enqueue %d, program will now exit\n", qElement);
		}
	}
	displayQueue(q, n);	
	//now the queue is full, so we start the operations
	//We dequeue an element, say this element as qElement
	//qElement = qElement - rValue
	//rvalue is some fixed number
	//if(qElement > 0)
	//	enqueue(qElement)
	//else
	//	drop qElement
	//continue this process till queue underflows (queue is empty)
	printf("Now we will do the operation : \n");
	while(isEmpty(q) == 0) {
		operationFlag = dequeue(q, &qElement, n);
		if(operationFlag == 0) {
			printf("Queue is empty! Program will end\n");
			break;
		}
		qElement = qElement - rValue;
		if(qElement > 0) {
			operationFlag = enqueue(q, qElement, n);
			if(operationFlag == 0){
				printf("Could not enqueue, program will exit\n");
				break;
			}
			displayQueue(q, n);
		}
		else {
			printf("Element %d (qElement - rvalue) is being dropped\n", qElement);
			displayQueue(q, n);
		}
	}
	return 0;
}

