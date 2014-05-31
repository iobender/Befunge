#ifndef BEFUNGE_H
#define BEFUNGE_H

#include "befunge_stack.h"

#define PROGRAM_ROWS 25
#define PROGRAM_COLS 80

struct position {
	int row;
	int col;
};

struct delta {
	int dx;
	int dy;
};

enum EDIRECTION { UP= 0, DOWN= 1, LEFT= 2, RIGHT= 3 };

void dirset(struct delta * dir, enum EDIRECTION where);

struct befunge_program {
	char code[PROGRAM_ROWS][PROGRAM_COLS]; /* befunge code */
	struct befunge_stack stack; /* stack for data */
	struct position ip; /* instruction pointer */
	struct delta dir; /* execution flow direction */
	int command_mode; /* whether or not we are in command mode or string mode */
};

int bf_init(struct befunge_program * bf);

int bf_load_code(struct befunge_program * bf, FILE * file);

void bf_moveip(struct befunge_program * bf);

void bf_run(struct befunge_program * bf);

void bf_process(struct befunge_program * bf);

void bf_destroy(struct befunge_program * bf);

#endif
