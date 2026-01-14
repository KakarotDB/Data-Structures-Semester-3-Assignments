#include <stdio.h>
#include <stdlib.h>
#define FREE(a)                                                                \
    {                                                                          \
        free(a);                                                               \
        a = NULL;                                                              \
    }
// implementing queue using circular queue
typedef struct {
    int front; // front of queue
    int rear;  // rear of queue, space right behind the last element.
    int *array;
} Queue;

Queue *createQ(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) {
        return NULL;
    }
    q->front = 0;
    q->rear = 0;

    q->array = (int *)malloc(size * sizeof(int));
    if (q->array == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        q->array[i] = 0; // 0 based initialization
    }

    return q;
}

int isFull(Queue *q, int size) {
    if (q == NULL) {
        return 0;
    }

    if (q->array == NULL) {
        return 0;
    }

    if ((q->rear + 1) % size == q->front) {
        return 1;
    }

    return 0;
}

int isEmpty(Queue *q) {
    if (q == NULL) {
        return 0;
    }

    if (q->array == NULL) {
        return 0;
    }

    if (q->rear == q->front) {
        return 1;
    }

    return 0;
}

int enqueue(Queue *q, int data, int size) { // enqueue at end of queue
    if (isFull(q, size) || q == NULL) {
        return 0;
    }
    q->array[q->rear] = data;
    q->rear = (q->rear + 1) % size;
    return 1;
}

int dequeue(Queue *q, int *dequed_element,
            int size) { // removes element from front of queue
    if (isEmpty(q) || q == NULL) {
        return 0;
    }
    *dequed_element = q->array[q->front];
    q->array[q->front] = 0;
    q->front = (q->front + 1) % size;
    return 1;
}

int freeQueue(Queue *q) {
    if (q != NULL) {
        FREE(q->array);
        FREE(q);
        return 1;
    }

    return 0;
}

void displayQueue(Queue *q, int size) { // displays queue
    if (q == NULL) {
        printf("Queue has not been created.\n");
        return;
    }
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    int current = q->front;
    while (current != q->rear) {
        printf("%d ", q->array[current]);
        current = (current + 1) % size;
    }
    printf("\n");
}

int main() {
    Queue *q = NULL;
    int element = 0;
    int size = 0;
    int choice = -1;
    int operationFlag = -1;
    while (1) {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Create Queue\n");
        printf("2. Enqueue\n");
        printf("3. Dequeue\n");
        printf("4. Check if Full\n");
        printf("5. Check if Empty\n");
        printf("6. Display Queue\n");
        printf("7. Free Queue and Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (q != NULL) {
                printf(
                    "Queue already exists. Please free it first (option 7).\n");
                break;
            }
            printf(
                "Enter the size of the queue: (Queue_Size = size_input - 1) ");
            scanf("%d", &size);
            q = createQ(size);
            if (q != NULL) {
                printf("Queue of size %d created successfully.\n", size - 1);
            } else {
                printf("Failed to create queue.\n");
            }
            break;

        case 2:
            if (q == NULL) {
                printf("Please create a queue first (option 1).\n");
                break;
            }
            printf("Enter the element to enqueue: ");
            scanf("%d", &element);
            operationFlag = enqueue(q, element, size);
            if (operationFlag) {
                printf("%d enqueued successfully.\n", element);
            } else {
                printf("Queue is full or not initialized.\n");
            }
            break;

        case 3:
            if (q == NULL) {
                printf("Please create a queue first (option 1).\n");
                break;
            }
            operationFlag = dequeue(q, &element, size);
            if (operationFlag) {
                printf("Dequeued element: %d\n", element);
            } else {
                printf("Queue is empty or not initialized.\n");
            }
            break;

        case 4:
            if (q == NULL) {
                printf("Please create a queue first (option 1).\n");
                break;
            }
            if (isFull(q, size)) {
                printf("The queue is full.\n");
            } else {
                printf("The queue is not full.\n");
            }
            break;

        case 5:
            if (q == NULL) {
                printf("Please create a queue first (option 1).\n");
                break;
            }
            if (isEmpty(q)) {
                printf("The queue is empty.\n");
            } else {
                printf("The queue is not empty.\n");
            }
            break;

        case 6:
            displayQueue(q, size);
            break;

        case 7:
            if (q != NULL) {
                freeQueue(q);
                q = NULL;
            }
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
            break;
        }
    }
    return 0;
}
