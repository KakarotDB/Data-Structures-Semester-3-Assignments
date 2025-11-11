#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include <string.h>
#include <ctype.h>
int main() {
    char expression[513];
    int result = 0;
    int size = 512;
    int operand2 = 0;
    int operand1 = 0;
    stack *s = (stack *) malloc(sizeof(stack));
	char number[20]; //this stores the current number to be pushed into the stack 
	int index = 0;
	int i = 0;
    int operationFlag = initialize(s, size);
	index = 0;
    if (0 == operationFlag)
    {
        printf("Could not initialize stack ! Error occurred, program will now terminate\n");
        return -1;
    }
    
    printf("Enter a postfix expression (up to 512 characters) (separated by spaces) : ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; /* replacing newline character from 
                                                    fgets with null terminating character */
    //char *token = strtok(expression, " "); 
    //We assume that operators and operands are separated by spaces (Eg : a b -)
	while(expression[i] != '\0') {
		if(isspace(expression[i])
				continue;
		if(expression[i] != ' ' && isdigit(expression[i])) { //current character is not a space, but a digit
			number[index] = expression[i]; //forming the number
			index++;
		}
		else if(expression[i] != ' ' && !isdigit(expression[i])) { //current character is not a space, and not a digit
			operationFlag = pop(s, &operand2); //first popped element from stack is operand2
			if(0 == operationFlag) {
				printf("Invalid expression! Could not get operand2\n");
				return -1;
			}
			operationFlag = pop(s, &operand1); //second popped element from stack is operand1
			if(0 == operationFlag) {
				printf("Invalid expression! Could not get operand1\n");
				return -1;
			}
	        switch (expression[i]) //finding what type of operation
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
                printf("Error! Invalid character in expression. \n"); //The current character is not an operator nor digit
																	  //thus must be invalid character	
                break;
            }			
		}
		else if(expression[i] == ' ' && isdigit(expression[i - 1])) {
			//to Push a number into stack, current character must be a space, and the previous must be a digit
			number[index] = '\0';
			push(s, atoi(number), size);
			index = 0;
			//printf("%s\n", number);
			//printf("%s\n", number);
		}
		i++;
	}
//	for(int i = 0; i < size; i++)
//		printf("%d ",s->array[i]); 
    operationFlag = pop(s, &result);
    if (0 == operationFlag)
    {
        printf("Could not get result\n");
        return -1;
    }
    if (0 == isEmpty(s))
    {
        printf("Error : Invalid postfix expression\n");
        return -1;
    }
    printf("Result = %d\n", result);

	return 0;
}
