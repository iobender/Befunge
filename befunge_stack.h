/* 
 * Matthew Bender
 * May 29, 2014
 *
 * declarations for Befunge stack 
 * convention is to name functions starting with bfs_
 */
#ifndef BEFUNGE_STACK_H
#define BEFUNGE_STACK_H

/* stack used in a Befunge program, consisting of ints */
struct befunge_stack {
	int * data; /* pointer to the stack, implemented as an array */
	int size; /* number of elements in the stack */
	int capacity; /* capacity of the stack before it needs to be resized */
};

/* initializes the stack */
int bfs_init(struct befunge_stack * stack);

/* pushes an element onto the stack */
int bfs_push(struct befunge_stack * stack, int elt);

/* pops an element from the stack */
int bfs_pop(struct befunge_stack * stack);

/* peeks at an item from the stack */
int bfs_peek(struct befunge_stack * stack);

/* prints the contents of the stack */
void bfs_print(struct befunge_stack * stack);

/* destroys the stack and all memory it has */
void bfs_destroy(struct befunge_stack * stack);

#endif
