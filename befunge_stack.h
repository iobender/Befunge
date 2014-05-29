#ifndef BEFUNGE_STACK_H
#define BEFUNGE_STACK_H

struct befunge_stack {
	int * data;
	int size;
	int capacity;
};

int bs_init(struct befunge_stack * stack);

int bs_push(struct befunge_stack * stack, int elt);
int bs_pop(struct befunge_stack * stack);
int bs_peek(struct befunge_stack * stack);

void bs_destroy(struct befunge_stack * stack);

#endif
