/*
 * Matthew Bender
 * May 29, 2014
 * 
 * Implementations for Befunge stack methods
 */
#include <stdio.h>
#include <stdlib.h>
#include "befunge_stack.h"

/*
 * Initializes an empty stack
 * Sets size to be 0, 
 * sets capacity to be default, 
 * and allocates memory for capacity number of elements
 * returns 1 if allocation was successful, else 0
 */
int bfs_init(struct befunge_stack * stack) {
	stack->size= 0;
	stack->capacity= DEFAULT_INIT_STACK_CAPACITY;
	stack->data= malloc(stack->capacity * sizeof(int));
	return stack->data != NULL;
}

/*
 * Pushes an element to the stack. 
 * Resizes the stack if necessary to make room for more elements 
 * Returns 0 if memory allocation was necessary and it failed, else 1
 */
int bfs_push(struct befunge_stack * stack, int elt) {
	/* if we need more space for the stack, double its capacity */
	if(stack->size == stack->capacity) {
		int * new= realloc(stack->data, 2 * stack->capacity * sizeof(int));
		if(new) {
			stack->data= new;
			stack->capacity *= 2;
		} else {
			return 0; /* allocation failed */
		}
	}
	/* stack builds towards the end of the array */
	stack->data[stack->size++]= elt;
	return 1;
}

/*
 * Pops an item from the stack. 
 * Popping from an empty stack will return 0.
 * Returns the popped element
 */
int bfs_pop(struct befunge_stack * stack) {
	if(stack->size) {
		return stack->data[--stack->size]; /* return element and decrease size */
	} else { /* empty stack */
		return 0;
	}
}

/*
 * Peeks at the top item on the stack.
 * Peeking at an empty stack returns 0.
 * Does not modify the stack.
 * Returns the top element on the stack.
 */
int bfs_peek(struct befunge_stack * stack) {
	if(stack->size) {
		return stack->data[stack->size - 1];
	} else { /* empty stack */
		return 0; 
	}
}

/*
 * Prints the contents of the stack.
 * Everything is printed as an integer, so characters have their ASCII values printed 
 */
void bfs_print(struct befunge_stack * stack) {
	int i= stack->size;
	while(i--) {
		int elt= stack->data[i];
		printf("%d \n", elt);
	}
	printf("\n");
}

/*
 * Frees all memory allocated for the stack.
 */
void bfs_destroy(struct befunge_stack * stack) {
	free(stack->data);
}

