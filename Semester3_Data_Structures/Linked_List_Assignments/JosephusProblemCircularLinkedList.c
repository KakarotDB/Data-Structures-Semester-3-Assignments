#include <stdio.h>
#include <stdlib.h>

typedef struct person {
    int ID;
    struct person *next;
} person;

int insertPerson(person **start, int ID) {
    if (start == NULL)
        return 0; // invalid list

    person *newPerson = (person *)malloc(sizeof(person));

    if (newPerson == NULL)
        return 0; // memory allocation failed

    newPerson->ID = ID;
    newPerson->next = newPerson;

    if (*start == NULL) { // first node to be inserted
        *start = newPerson;
        return 1;
    }

    newPerson->next = (*start)->next;
    (*start)->next = newPerson;
    *start = newPerson; // the head always points to the last person in the
                        // circular list
    return 1;
}

int createCircle(person **start, int n) {
    if (start == NULL)
        return 0; // invalid list

    *start = NULL;

    for (int i = 1; i <= n; i++) {
        if (insertPerson(start, i) == 0)
            return 0;
    }
    return 1;
}

int removeNextPerson(person **previous) {
    if (previous == NULL)
        return 0; // invalid list

    if (*previous == NULL) {
        return 1; // empty list
    }
    person *to_Delete = (*previous)->next;
    (*previous)->next = (*previous)->next->next;
    free(to_Delete);
    return 1;
}

int main() {
    person *head = NULL;
    int n = 0;
    int s = 0;
    int count_start = 1;

    printf("Enter the number of people (n) : ");
    scanf("%d", &n);
    if (createCircle(&head, n) == 1)
        printf("Successfully created the circle with %d people!\n", n);

    printf("Enter number of people (s) to be skipped : ");
    scanf("%d", &s);

    printf("From which person should the counting start? : ");
    scanf("%d", &count_start);

    if (count_start > n || count_start < 1) {
        printf("Count cannot be lesser than 1 or greater than n!\n");
        return -1;
    }

    while (head->ID != count_start)
        head = head->next;

    printf("Now simulating game : \n");

    while (head->next != head) {
        for (int i = 1; i < s; i++)
            head = head->next;

        printf("Person ID : %d is being removed\n", head->next->ID);
        removeNextPerson(&head);
        head = head->next;
    }
    printf("The winner is Person ID : %d\n", head->ID);
}
