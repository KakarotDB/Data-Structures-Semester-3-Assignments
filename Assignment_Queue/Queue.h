#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#define FREE(a) { free (a); a = NULL; }
typedef struct {
    int front; //front of queue
    int rear; //rear of queue, space right behind the last element.
    int *array;
} Queue;

Queue* createQ(int size) { 
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q == NULL)
    {
        return NULL;
    }
    q->front = 0;
    q->rear = 0;

    q->array = (int *) malloc(size * sizeof(int));
    if (q->array == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        q->array[i] = 0; //0 based initialization
    }

    return q;
}

int isFull(Queue* q, int size) { //over here, we sacrifice the last space in the array to check for isFull
    if (q == NULL)
    {
        return 0;
    }
    
    if (q->array == NULL)
    {
        return 0;
    }
    
    if ((q->rear + 1) % size == q->front)
    {
        return 1;
    }
    
    return 0;
}

int isEmpty(Queue* q) {
    if (q == NULL)
    {
        return 0;
    }

    if (q->array == NULL)
    {
        return 0;
    }
    
    if (q->rear == q->front)
    {
        return 1;
    }
    
    return 0;
}

int enqueue(Queue *q, int data, int size) { //enqueue at end of queue
    if (isFull(q, size) || q == NULL)
    {
        return 0;
    }
    q->array[q->rear] = data;
    q->rear = (q->rear + 1) % size;
    return 1;
}

int dequeue(Queue* q, int* dequed_element, int size) { //removes element from front of queue
    if (isEmpty(q) || q == NULL)
    {
        return 0;
    }
    *dequed_element = q->array[q->front];
    q->array[q->front] = 0;
    q->front = (q->front + 1) % size;
    return 1;
}

int freeQueue(Queue* q) {
    if (q != NULL)
    {
        FREE(q->array);
        FREE(q);
        return 2;
    }
    
    return 0;
}

void displayQueue(Queue* q, int size) { //displays queue
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

#endif
