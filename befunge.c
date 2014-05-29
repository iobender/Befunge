#include <stdio.h>

struct position {
	int row;
	int col;
}

struct befunge_program {
	char code[80][25]; /* befunge code */
	struct befunge_stack stack; /* stack for data */
	struct position ip; /* instruction pointer */
	struct direction dir; /* execution flow direction */
}
