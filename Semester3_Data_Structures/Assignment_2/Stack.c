#include <stdio.h>
#include <stdlib.h>
#define FREE(a)                                                                \
    {                                                                          \
        free(a);                                                               \
        a = NULL;                                                              \
    }
// For operations :
// 1 - success
// 0 - failure

typedef struct {
    int top_element; // points to top element of stack
    int *array;      // dynamically allocated array for implementation of stack
} stack;

int initialize(stack *s, int size) {
    s->top_element = -1; // initially there are no elements, thus -1.
    s->array = (int *)malloc(size * sizeof(int));
    if (s->array == NULL)
        return 0;
    for (int i = 0; i < size; i++) {
        s->array[i] = 0; // initializing all elements to 0
    }
    return 1;
}

int push(stack *s, int element, int size) {
    if (s->top_element + 1 == size)
        return 0; // stack is full, cannot push more elements
    s->array[++s->top_element] = element;
    return 1;
}

int pop(stack *s, int *dp) {
    if (s->array == NULL || s->top_element == -1)
        return 0; // array is NULL or there are no elements in the stack
    *dp = s->array[s->top_element];
    s->array[s->top_element] = 0;
    s->top_element--;

    return 1;
}

int freeStack(stack *s) {
    if (s == NULL || s->array == NULL)
        return 0; // does not refer to a valid stack
    FREE(s->array);
    FREE(s);
    return 1;
}

int isFull(stack *s, int size) {
    if (s == NULL || s->array == NULL) {
        return 0;
    }
    if (s->top_element + 1 == size)
        return 1;
    return 0;
}

int isEmpty(stack *s) {
    if (s == NULL || s->array == NULL)
        return 0;
    if (s->top_element == -1)
        return 1;
    return 0;
}
int main() {
    stack s;
    int element = 0;
    int size = 0;
    int choice = -1;
    int operation_flag = -1;
    int dp = 0;
    ;
    printf("Enter stack size : ");
    scanf("%d", &size);
    while (getchar() != '\n')
        ;
    operation_flag = initialize(&s, size);
    if (operation_flag == 0) {
        printf("Could not initialize Stack ! Program will terminate");
        return -1;
    }
    printf("Successfully initialized stack with 0 initialization!\n");
    printf("1. Push an element\n"
           "2. Pop an element\n"
           "3. Free stack\n"
           "4. Check if Stack is full\n"
           "5. Check if Stack is empty\n"
           "6. Print current stack\n");

    do {
        printf("\nEnter your choice (0 to exit): ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        switch (choice) {
        case 1: // push
            printf("Enter element to push : ");
            scanf("%d", &element);
            operation_flag = push(&s, element, size);
            if (operation_flag == 0)
                printf("Could not push to stack! Full/Not defined");
            else
                printf("Pushed %d to stack\n", element);
            break;
        case 2: // pop
            operation_flag = pop(&s, &dp);
            if (operation_flag == 0)
                printf("Stack empty/not defined\n");
            else
                printf("Popped element : %d\n", dp);
            break;
        case 3: // free stack
            operation_flag = freeStack(&s);
            if (0 == operation_flag)
                printf("Could not free stack. Stack invalid\n");
            else
                printf("Stack freed successfully\n");
            break;
        case 4: // isFull ?
            operation_flag = isFull(&s, size);
            if (0 == operation_flag)
                printf("Stack is not full/invalid stack\n");
            else
                printf("Stack is full\n");
            break;
        case 5: // isEmpty ?
            operation_flag = isEmpty(&s);
            if (0 == operation_flag)
                printf("Stack is not empty/invalid stack\n");
            else
                printf("Stack is empty\n");
            break;
        default:
            printf("Wrong choice/exited program!\n");
        }
    } while (choice != 0);
    freeStack(&s);
}
