#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include <string.h>
#include <ctype.h>
int main() {
    char expression[513];
    int size = 512;
    int operand2 = 0;
    int operand1 = 0;
    stack *s = (stack *) malloc(sizeof(stack));
    int operationFlag = initialize(s, size);
    if (0 == operationFlag)
    {
        printf("Could not initialize stack ! Error occurred, program will now terminate\n");
        return -1;
    }
    
    printf("Enter a postfix expression (up to 512 characters) (separated by spaces) : ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; /* replacing newline character from 
                                                    fgets with null terminating character */
    char *token = strtok(expression, " "); 
    //we separate the strings into tokens, separated using delimiter " ", this makes it easier
    //for us to to manage multiple digit numbers 
    //We assume that operators and operands are separated by spaces (Eg : a b -)
    while(token != NULL) {
        if (isdigit(token[0]))
        {
            push(s, atoi(token), size); 
        }
        else {
            operationFlag = pop(s, &operand2);
            if (0 == operationFlag)
            {
                printf("Invalid expression!\n");
                return -1;
            }
            operationFlag = pop(s, &operand1);
            if (0 == operationFlag)
            {
                printf("Invalid expression!\n");
                return -1;
            }
            switch (token[0])
            {
            case '+':
                push(s, operand1 + operand2, size);
                break;
            case '-':
                push(s, operand1 - operand2, size);
                break;
            case '*':
                push(s, operand1 * operand2, size);
                break;
            case '/':
                if (operand2 == 0)
                {
                    printf("Error! Division by zero\n");
                    return -1;
                }

                push(s, operand1 / operand2, size);
                break;
            
            default:
                printf("Error! Invalid character in expression. \n");
                break;
            }

        }
        //get the next token
        token = strtok(NULL, " ");
    }
    int result = 0;
    operationFlag = pop(s, &result);
    if (0 == operationFlag)
    {
        printf("Could not get result");
        return -1;
    }
    if (0 == isEmpty(s))
    {
        printf("Error : Invalid postfix expression");
        return -1;
    }
    printf("Result = %d\n", result);
	freeStack(s);
	return 0;
}
