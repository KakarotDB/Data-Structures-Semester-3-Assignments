#define FREE(a) { free(a); a = NULL; }
//For operations : 
//1 - success
//0 - failure

typedef struct{
	int top_element; //points to top element of stack
	int *array; //dynamically allocated array for implementation of stack 
} stack;

int initialize(stack *s, int size){
	s->top_element = -1; //initially there are no elements, thus -1.
	s->array = (int *) malloc(size*sizeof(int));
	if(s->array == NULL)
		return 0;
	for(int i = 0; i < size; i++){
		s->array[i] = 0; //initializing all elements to 0
	}
	return 1;
}

int push(stack *s, int element, int size){
	if(s->top_element + 1 == size)
		return 0; //stack is full, cannot push more elements
	s->array[++s->top_element] = element;
	return 1;
}

int pop(stack *s, int *dp){
	if(s->array == NULL || s->top_element == -1)
		return 0; //array is NULL or there are no elements in the stack
	*dp = s->array[s->top_element];
	s->array[s->top_element] = 0;
	s->top_element--;
	
	return 1;
}

int freeStack(stack *s){
	if(s == NULL || s->array == NULL)
		return 0; //does not refer to a valid stack
	FREE(s->array);
	return 1;
}

int isFull(stack *s, int size) {
	if(s == NULL || s->array == NULL) {
		return 0;
	}
	if(s->top_element + 1 == size)
		return 1;
	return 0;
}

int isEmpty(stack *s) {
	if(s == NULL || s->array == NULL)
		return 0;
	if(s->top_element == -1)
		return 1;
	return 0;
}
