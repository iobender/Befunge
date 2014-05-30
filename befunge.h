#ifndef BEFUNGE_H
#define BEFUNGE_H

#include "befunge_stack.h"

#define PROGRAM_ROWS 80
#define PROGRAM_COLS 25

struct position {
	int row;
	int col;
};

struct delta {
	int dx;
	int dy;
};

enum EDIRECTION { UP, DOWN, LEFT, RIGHT };

struct befunge_program {
	char code[PROGRAM_ROWS][PROGRAM_COLS]; /* befunge code */
	struct befunge_stack stack; /* stack for data */
	struct position ip; /* instruction pointer */
	struct delta dir; /* execution flow direction */
};

#endif
