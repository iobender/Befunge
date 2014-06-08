/*
 * Matthew Bender
 * May 29, 2014
 *
 * declarations for Befunge code interpreter 
 * convention is to name functions starting with bfg_
 */
#ifndef BEFUNGE_H
#define BEFUNGE_H

#include "befunge_stack.h"

#define PROGRAM_ROWS 25
#define PROGRAM_COLS 80

/* used to represent where in the playfield we are */
struct position {
	int row;
	int col;
};

/* used to represent which direction we are going */
struct delta {
	int dx;
	int dy;
};

enum EDIRECTION { UP= 0, DOWN= 1, LEFT= 2, RIGHT= 3 };

/* sets delta x and y based on direction */
void dirset(struct delta * dir, enum EDIRECTION where);

/* core structure representing a Befunge program */
struct befunge_program {
	char code[PROGRAM_ROWS][PROGRAM_COLS]; /* befunge code */
	struct befunge_stack stack; /* stack for data */
	struct position ip; /* instruction pointer */
	struct delta dir; /* execution flow direction */
	int command_mode; /* whether or not we are in command mode or string mode */
};

/* initializes Befunge program */
int bfg_init(struct befunge_program * bf);

/* reads Befunge code from a file and stores it */
void bfg_load_code(struct befunge_program * bf, FILE * file);

/* advances the instruction pointer in the right direction */
void bfg_moveip(struct befunge_program * bf);

/* runs the Befunge program that has been loaded */
void bfg_run(struct befunge_program * bf);

/* processes a single instruction */
void bfg_process(struct befunge_program * bf);

/* destroys the Befunge program structure and all its memory */
void bfg_destroy(struct befunge_program * bf);

#endif
