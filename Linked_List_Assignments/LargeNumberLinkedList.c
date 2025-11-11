#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int digit;
    struct node *next;
} node;

typedef struct {
    node *head;
    int isPositive;
} largeNumber;

int insert(node **start, int element) // inserting node at head
{
    node *newNode = NULL;
    newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed !\n");
        return 0;
    }

    newNode->digit = element;
    newNode->next = NULL;

    if (*start == NULL) // empty list
    {
        *start = newNode;
        return 1;
    }

    node *head = *start;
    newNode->next = head; // make before break;
    *start = newNode;

    return 1;
}

int compareMagnitude(largeNumber n1, largeNumber n2) {
    int len1 = 0, len2 = 0;
    node *temp1 = n1.head;
    node *temp2 = n2.head;
    while (temp1 != NULL) {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        len2++;
        temp2 = temp2->next;
    }

    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1; // comparing the number of digits of both numbers

    char str1[len1 + 1], str2[len2 + 1]; // storing both numbers in strings

    int i = len1 - 1;
    temp1 = n1.head;
    while (temp1) {
        str1[i--] = temp1->digit + '0';
        temp1 = temp1->next;
    }
    str1[len1] = '\0';

    temp2 = n2.head;
    i = len2 - 1;
    while (temp2) {
        str2[i--] = temp2->digit + '0';
        temp2 = temp2->next;
    }
    str2[len2] = '\0';

    int compare = strcmp(str1, str2); // using string compare
    if (compare > 0)
        return 1;
    if (compare < 0)
        return -1;
    return 0;
}

int subtractNumbers(node *larger, node *smaller, node **result) {
    if (larger == NULL || smaller == NULL || result == NULL) {
        return 0;
    }

    *result = NULL;
    node *temp1 = larger;
    node *temp2 = smaller;
    int borrow = 0;

    while (temp1 != NULL) {
        int d1 = temp1->digit;
        int d2 = (temp2 != NULL) ? temp2->digit : 0;

        int difference = d1 - d2 - borrow;
        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else
            borrow = 0;
        insert(result, difference);
        temp1 = temp1->next;
        if (temp2 != NULL) {
            temp2 = temp2->next;
        }
    }
    return 1;
}

int addNumbers(largeNumber n1, largeNumber n2,
               largeNumber *sum) { // subtraction can be thought of as addition
                                   // with a negative number
    if (sum == NULL || n1.head == NULL || n2.head == NULL) {
        return 0;
    }

    sum->head = NULL;

    if (n1.isPositive ==
        n2.isPositive) // addition of two positive/negative numbers
    {
        sum->isPositive = n1.isPositive;
        node *temp1 = n1.head;
        node *temp2 = n2.head;
        int carry = 0;
        while (temp1 != NULL || temp2 != NULL) {
            int d1 = (temp1 != NULL) ? temp1->digit : 0;
            int d2 = (temp2 != NULL) ? temp2->digit : 0;
            int s = d1 + d2 + carry;
            insert(&(sum->head), s % 10);
            carry = s / 10;
            if (temp1 != NULL)
                temp1 = temp1->next;
            if (temp2 != NULL)
                temp2 = temp2->next;
        }
        if (carry > 0) {
            insert(&(sum->head), carry);
        }
    } else // subtraction : a - b = a + (- b)
    {
        int comparison = compareMagnitude(n1, n2);
        if (comparison == 0) {
            sum->isPositive = 1;
            insert(&(sum->head), 0);
            return 1;
        }

        if (comparison > 0) // n1 > n2
        {
            sum->isPositive = n1.isPositive;
            subtractNumbers(n1.head, n2.head, &(sum->head));
        } else {
            sum->isPositive = n2.isPositive;
            subtractNumbers(n2.head, n1.head, &(sum->head));
        }
    }
    return 1;
}

// function to divide a large number by 16 and return the remainder
int divideBy16(node **start) {
    node *temp = *start;
    int remainder = 0;

    // performing long division
    while (temp != NULL) {
        int current_val = remainder * 10 + temp->digit;
        temp->digit = current_val / 16;
        remainder = current_val % 16;
        temp = temp->next;
    }

    // removing leading zeroes after division
    while (*start != NULL && (*start)->digit == 0) {
        node *to_free = *start;
        *start = (*start)->next;
        free(to_free);
    }
    return remainder;
}

void printHexadecimal(largeNumber n) {
    if (n.head == NULL) {
        printf("0\n");
        return;
    }

    node *temp_head = NULL;
    node *current = n.head;

    // creating a tempoary coppy to prevent destruction of original number
    while (current != NULL) {
        insert(&temp_head, current->digit);
        current = current->next;
    }

    char hex_rev[512] = {0}; // string to store the digits in reverse
    int i = 0;

    while (temp_head != NULL) {
        int remainder = divideBy16(&temp_head);
        if (remainder < 10) {
            hex_rev[i++] = remainder + '0';
        } else {
            hex_rev[i++] = remainder - 10 + 'A';
        }
    }

    if (n.isPositive == 0) {
        printf("-"); // printing sign for negative number
    }

    // printing hexadecimal string in correct (reversed) order
    printf("0x");
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hex_rev[j]);
    }
    printf("\n");
}
void printList(node *start) {
    if (start == NULL) {
        return;
    }

    node *temp = start;
    while (temp != NULL) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    largeNumber n1, n2;
    n1.head = NULL;
    n2.head = NULL;
    n1.isPositive = 1;
    n2.isPositive = 1;
    int i = 0;
    char str1[512];
    char str2[512];

    printf("Enter first number : ");
    fgets(str1, 512, stdin);
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second number : ");
    fgets(str2, 512, stdin);
    str2[strcspn(str2, "\n")] = '\0';

    if (str1[0] == '-') {
        n1.isPositive = 0;
        i++;
    }
    while (str1[i] != '\0') {
        insert(&(n1.head), str1[i] - '0');
        i++;
    }
    i = 0;
    if (str2[0] == '-') {
        n2.isPositive = 0;
        i++;
    }
    while (str2[i] != '\0') {
        insert(&(n2.head), str2[i] - '0');
        i++;
    }

    printf("First number in hexadecimal format : \n");
    printHexadecimal(n1);
    printf("Second number in hexadecimal format : \n");
    printHexadecimal(n2);

    largeNumber sum;
    sum.head = NULL;
    addNumbers(n1, n2, &sum);
    printf("Sum = ");
    if (sum.isPositive == 1) {
        printList(sum.head);
        printf("Sum in hexadecimal format : \n");
        printHexadecimal(sum);
    } else {
        printf("-");
        printList(sum.head);
        printf("Sum in hexadecimal format : \n");
        printHexadecimal(sum);
    }
    return 0;
}
