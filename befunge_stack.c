#include <stdio.h>
#include <stdlib.h>
#include "befunge_stack.h"

#define DEFAULT_INIT_STACK_CAPACITY 64

int bfs_init(struct befunge_stack * stack) {
	stack->size= 0;
	stack->capacity= DEFAULT_INIT_STACK_CAPACITY;
	stack->data= malloc(stack->capacity * sizeof(int));
	return stack->data != NULL;
}

int bfs_push(struct befunge_stack * stack, int elt) {
	/* check if we need more space for stack. Separate into own function */
	if(stack->size == stack->capacity) {
		int * new= realloc(stack->data, 2 * stack->capacity * sizeof(int));
		if(new) {
			stack->data= new;
			stack->capacity *= 2;
		} else {
			return 0;
		}
	}
	stack->data[stack->size++]= elt;
	return 1;
}

int bfs_pop(struct befunge_stack * stack) {
	if(stack->size) {
		return stack->data[--stack->size];
	} else {
		return 0; /* popping from an empty stack returns 0 */
	}
}

int bfs_peek(struct befunge_stack * stack) {
	if(stack->size) {
		return stack->data[stack->size - 1];
	} else {
		return 0; /* peeking at an empty stack returns 0 */
	}
}

void bfs_destroy(struct befunge_stack * stack) {
	free(stack->data);
	free(stack);
}

void bfs_print(struct befunge_stack * stack) {
	int i= stack->size;
	while(i--) {
		int elt= stack->data[i];
		printf("%d \n", elt);
	}
	printf("\n");
}

