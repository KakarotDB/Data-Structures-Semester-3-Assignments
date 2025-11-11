#include <stdio.h>
#include "Stack.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
int main(){
	stack Stack;
	int i = 0;
	char input[512];
    int popped_element = 0;
	int operationFlag = -1;
    bool check = true;

	printf("Enter mathematical expression : ");
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")] = '\0';

	initialize(&Stack, 512);

	while(input[i] != '\0'){
        if (isalnum(input[i]) || isspace(input[i]))
        {
            i++;
            continue;
        }
        if (input[i] == '(') {
            operationFlag = push(&Stack, 0, 512);
        } 
        else if (input[i] == '[') {
            operationFlag = push(&Stack, 1, 512);
        } 
        else if (input[i] == '{') {
            operationFlag = push(&Stack, 2, 512);
        }
        else if (input[i] == ')') {
            operationFlag = pop(&Stack, &popped_element);
            if (operationFlag == 0 || popped_element != 0) {
                check = false;
                break;
            }
        } 
        else if (input[i] == ']') {
            operationFlag = pop(&Stack, &popped_element);
            if (operationFlag == 0 || popped_element != 1) {
                check = false;
                break;
            }
        } 
        else if (input[i] == '}') {
            operationFlag = pop(&Stack, &popped_element);
            if (operationFlag == 0 || popped_element != 2) {
                check = false;
                break;
            }
        }
        i++;
	}
    if (check && isEmpty(&Stack))
    {
        printf("Valid expression\n");
    }
    else
        printf("Not a valid expression\n");
    
    
}
