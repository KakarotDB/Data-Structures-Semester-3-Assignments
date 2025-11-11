#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct node{
    int data; //node : [data, next]
    struct node *next; //points to next node
} node;

//structure would look like a -> b -> c -> null

int addListNodeSorted(node **start_ref, int element) {
    node *newNode = NULL;
    newNode = (node *) malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return 0; //failure
    }

    newNode->data = element;
    newNode->next = NULL;
    
    //case 1 : Empty list / new node is new head 
    if(*start_ref == NULL || element > (*start_ref)->data) {
        newNode->next = *start_ref;
        *start_ref = newNode;
        return 1; //success
    }

    //case 2 : Finding correct position to insert node
    node *current = *start_ref;
    while (current->next != NULL && current->next->data > element) 
    {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode; //make before break
    return 1;
}

int isNodePresent(node *start, int element, int *position) {
    node* current = start; 
    int pos = 1; //holding current position
    while(current != NULL) {
        if (current->data == element)
        {
            *position = pos;
            return 1; //success
        }
        current = current->next;
        pos++;
    }
    return 0; //failure
}

int deleteNode(node** start, int element) {
    node* temp = *start;
    node* prev = NULL;
	if (temp == NULL)
	{
		return 0;
	}
	
    if (element > temp->data && temp != NULL) //Element > first element (Descending order), so not in list
    {
        return 0;
    }
    
    if (temp != NULL && temp->data == element) //element to be deleted is head
    {
        *start = temp->next;
        free(temp);
        return 1;
    }
    
    while (temp != NULL && temp->data != element)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return 0; //could not find element to be deleted;
    }

    prev->next = temp->next;
    free(temp);
    return 1;

}

int freeListNodeSorted(node **start) {
	if(*start == NULL)
        return 1; //list is already empty
    
    node* current = *start;
    node* nextNode = NULL;

    while(current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *start = NULL;
    return 1;
}

node* reverseListNodeSorted(node* start) {
	//using recursion to reverse the list
	//base cases
	if(start == NULL || start->next == NULL) {
		return start;
	}

	//recursive call to reverse list 
	node* newHead = reverseListNodeSorted(start->next);

	start->next->next = start; //reversing the link 
	start->next = NULL;
	return newHead;
}

void updateListNode(node *start) {
	node * temp = start;
	while(temp != NULL) {
		int random = rand() % 10;
		temp->data += random;
		temp = temp->next;
	}
}

node* sortListNode(node* start) { //using insertion sort
	node* sortedList = NULL; //head of sorted list
	node* nextUnsorted;
	node* traverse;
	node* current = start;

	while(current != NULL) {
		nextUnsorted = current->next; //holding the next node

		if (sortedList == NULL || current->data >= sortedList->data)
		{
			current->next = sortedList; //inserting element to head of list 
			sortedList = current;
		}
		else 
		{
			traverse = sortedList; //holding the sorted list 
			while (traverse->next != NULL && traverse->next->data > current->data)
			{
				traverse = traverse->next; //finding the correct insertion point
			}

			current->next = traverse->next; //de-linking node
			traverse->next = current; //linking node
			
		}

		current = nextUnsorted; //going to the next unsorted element 
	}
	return sortedList;
}

node* mergeListNodeSorted(node* start1, node* start2){
	node* mergedList = NULL;
	//putting first node into mergedList
	if(start1->data >= start2->data){
		mergedList = start1;
		start1 = start1->next;
	}
	else {
		mergedList = start2;
		start2 = start2->next;
	}
	node* traverse = mergedList;
	while(start1 != NULL && start2 != NULL) {
		if(start1->data >= start2->data) {
			traverse->next = start1;
			start1 = start1->next;
		}
		else {
			traverse->next = start2;
			start2 = start2->next;
		}
		traverse = traverse->next;
	}
	if(start1 != NULL) {
		while(start1 != NULL) {
			traverse->next = start1;
			start1 = start1->next;
			traverse = traverse->next;
		}
	}
	else {
		while(start2 != NULL) {
			traverse->next = start2;
			start2 = start2->next;
			traverse = traverse->next;
		}
	}
	traverse->next = NULL;
	return mergedList;
}
void printLinkedList(node* start) {
	if(start == NULL) {
		printf("NULL\n");
	}
	node* temp = start;
	while(temp != NULL) {
		if(temp->next == NULL) {
			printf("%d\n", temp->data);
			break;
		}
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
}

int main() {
	//variable declaration zone
	srand(time(NULL));
	node* head = NULL;
	node* head1 = NULL;
	node* head2 = NULL;
	node* merged = NULL;
	int n1 = 0;
	int n2 = 0;
	int operationFlag = -1;
	int element = 0;
	int choice = -1;
	int pos;
	do {
		printf("0. Exit program\n"	
			   "1. Add node to list\n"
			   "2. Check if an element is present\n"
			   "3. Delete a target element\n"
			   "4. Print current linked list\n"
			   "5. Free linked list\n"
			   "6. Reverse linked list\n"
			   "7. Add a random value to each node\n"
			   "8. Sort the list\n"
			   "9. Make two lists, and merge them\n"
			   "Enter your choice : ");
		scanf("%d", &choice);
		switch(choice) {
			case 0 :
				printf("Program exiting\n");
				break;
			case 1 :
				printf("Enter element to be inserted : ");
				scanf("%d", &element);
				operationFlag = addListNodeSorted(&head, element);
				if(0 == operationFlag)
					printf("Failed to add node\n");
				break;
			case 2 :
				printf("Enter element to be searched : ");
				scanf("%d", &element);
				operationFlag = isNodePresent(head, element, &pos); 
				if(0 == operationFlag)
					printf("Could not find element in list!\n");
				else
					printf("Found element at position : %d\n", pos);
				break;
			case 3 :
				printf("Enter target element to be deleted : ");
				scanf("%d", &element);
				operationFlag = deleteNode(&head, element);
				if(0 == operationFlag)
					printf("Could not find element to be deleted\n");
				else
					printf("Successfully deleted element %d!\n", element);
				break;
			case 4 :
				printf("Current linked list : \n");
				printLinkedList(head);
				break;
			case 5 :
				operationFlag = freeListNodeSorted(&head);
				if(operationFlag == 1)
					printf("Successfully freed list!\n");
				else
					printf("Could not free list!\n");
				break;
			case 6 : 
				printf("The list has  been reversed!");
				head = reverseListNodeSorted(head);
				break;
			case 7 : 
				updateListNode(head);
				printf("The list has been updated with random values added to each node!\n");
				break;
			case 8 :
				head = sortListNode(head);
				printf("The list has been sorted!\n");
				break;
			case 9 :
				head1 = NULL;
				head2 = NULL;
				merged = NULL;
				printf("Enter number of elements of list 1 : \n");
				scanf("%d", &n1);
				printf("Enter number of elements of list 2 : \n");
				scanf("%d", &n2);
				printf("Enter %d elements to list 1 : \n", n1);
				while(n1 > 0) {
					scanf("%d", &element);
					operationFlag = addListNodeSorted(&head1, element);
					if(operationFlag != 1){
						printf("Error adding node to list !\n");
						break;
					}
					n1--;
				}
				printf("Enter %d elements to list 2 : \n", n2);
				while(n2 > 0) {
					scanf("%d", &element);
					operationFlag = addListNodeSorted(&head2, element);
					if(operationFlag != 1){
						printf("Error adding node to list !\n");
						break;
					}
					n2--;
				}
				printf("List 1 : \n");
				printLinkedList(head1);
				printf("\n");
				printf("List 2 : \n");
				printLinkedList(head2);
				printf("\n");
				merged = mergeListNodeSorted(head1, head2);
				printf("Merged linked list : \n");
				printLinkedList(merged);
				n1 = 0;
				n2 = 0;
				freeListNodeSorted(&merged);
				break;
			default : 
				printf("Wrong choice !\n");
				break;
		}

	}
	while(choice != 0);
	return 0;
}
