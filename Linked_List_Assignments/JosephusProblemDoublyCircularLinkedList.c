#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person {
    int ID;
    struct person *next;
    struct person *previous;
} person; // circular doubly linked list

int insertPerson(person **start, int ID) {
    if (start == NULL) {
        return 0; // invalid list
    }

    person *newPerson = (person *)malloc(sizeof(person));

    if (newPerson == NULL)
        return 0; // memory allocation failed

    newPerson->ID = ID;
    newPerson->next = newPerson;
    newPerson->previous = newPerson;

    if (*start == NULL) {
        *start = newPerson;
        return 1; // newPerson is the start of the list
    }

    newPerson->next = *start;
    newPerson->previous = (*start)->previous;
    (*start)->previous = newPerson;
    newPerson->previous->next = newPerson;
    *start = newPerson;

    return 1;
}

int createCircle(person **head, int n) {
    if (head == NULL)
        return 0;

    *head = NULL;

    for (int i = 1; i <= n; i++) {
        if (insertPerson(head, i) == 0)
            return 0;
    }
    return 1;
}

int removeNextPerson(person **previous) {
    if (previous == NULL) {
        return 0;
    }

    if (*previous == NULL) {
        return 1;
    }

    person *to_delete = (*previous)->next;
    (*previous)->next = (*previous)->next->next;
    (*previous)->next->previous = *previous;
    free(to_delete);

    return 1;
}

int main() {
    person *head = NULL;
    int n = 0;
    int s = 0;
    int count_start = 1;
    int sign = 1;
    srand(time(NULL));

    printf("Enter number of people (n) : ");
    scanf("%d", &n);

    if (createCircle(&head, n) == 0) {
        printf("Could not create circle with n people!\n");
        return -1;
    } else {
        printf("Successfully created circle!\n");
    }

    printf("From which person should the counting start? : ");
    scanf("%d", &count_start);

    if (count_start > n || count_start < 1) {
        printf("Count cannot be lesser than 1 or greater than n!\n");
        return -1;
    }

    while (head->ID != count_start) {
        head = head->next;
    }

    printf("Now simulating game : \n");

    while (head->next != head) {
        sign = rand() % 2 == 1 ? 1 : -1;
        s = sign * (rand() % n + 1);

        printf("For this iteration the number of people to be skipped is %d, "
               "(negative -> anti clockwise) (positive -> clockwise)\n",
               s);

        if (s > 0) {
            for (int i = 1; i < abs(s); i++) {
                head = head->next;
            }
        } else {
            for (int i = 1; i < abs(s); i++) {
                head = head->previous;
            }
        }

        printf("Person ID %d is being removed\n", head->next->ID);
        removeNextPerson(&head);
        if (s > 0) {
            head = head->next;
        } else
            head = head->previous;
    }

    printf("Person %d is the winner of the game!\n", head->ID);

    return 0;
}
