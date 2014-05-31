#ifndef BEFUNGE_STACK_H
#define BEFUNGE_STACK_H

struct befunge_stack {
	char * data;
	int size;
	int capacity;
};

int bfs_init(struct befunge_stack * stack);

int bfs_push(struct befunge_stack * stack, char elt);
char bfs_pop(struct befunge_stack * stack);
char bfs_peek(struct befunge_stack * stack);

void bfs_destroy(struct befunge_stack * stack);

void bfs_print(struct befunge_stack * stack);

#endif
