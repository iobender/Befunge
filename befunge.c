#include <stdio.h>

struct befunge_program {
	char code[80][25]; /* befunge code */
	struct befunge_stack stack; /* stack for data */
	struct pos ip; /* instruction pointer */
	struct direction dir; /* execution flow direction */
}
