#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "befunge.h"
#include "befunge_stack.h"

/*
 * sets the delta x and y for dir depending on the direction passed 
 */
void dirset(struct delta * dir, enum EDIRECTION where) {
	switch(where) {
		case UP: /* ^ */
			dir->dx= 0;
			dir->dy= -1;
			break;
		case DOWN: /* v */
			dir->dx= 0;
			dir->dy= 1;
			break;
		case LEFT: /* < */ 
			dir->dx= -1;
			dir->dy= 0;
			break;
		case RIGHT: /* > */
			dir->dx= 1;
			dir->dy= 0;
			break;
	}
}

/*
 * Initializes the Befunge program structure.
 * Start with a fresh stack,
 * the instruction pointer in the top left,
 * pointing to the right,
 * and in command mode.
 * Returns 1 if successful, else 0.
 */
int bfg_init(struct befunge_program * bf) {
	int row, col;
	if(!bfs_init(&bf->stack)) return 0; /* if stack init fails then fail */
	bf->ip.row= 0;
	bf->ip.col= 0;
	dirset(&bf->dir, RIGHT);
	bf->command_mode= 1;
	/* initialize with spaces */
	for(row= 0; row < PROGRAM_ROWS; row++) {
		for(col= 0; col < PROGRAM_COLS; col++) {
			bf->code[row][col]= ' ';
		}
	}
	return 1;
}

/*
 * Loads the Befunge code from the Befunge file into the code field of the struct
 * Reads at most PROGRAM_ROWS lines of PROGRAM_COLS characters from the file
 */
void bfg_load_code(struct befunge_program * bf, FILE * file) {
	int row, col;
	/* read line by line, until PROGRAM_ROWS lines have been read of EOF */
	for(row= 0; row < PROGRAM_ROWS; row++) {
		/* TODO: fix number of chars read */
		if(fgets(bf->code[row], PROGRAM_COLS, file) == NULL) break;
		*strchr(bf->code[row], '\n')= ' '; /* get rid of newline */
		bf->code[row][strlen(bf->code[row])]= ' '; /* get rid of null char */
	}
}

/*
 * Moves the current instruction pointer 1 cell in the direction
 * specified by bf->dir.
 * Wraps around on all 4 sides 
 */
void bfg_moveip(struct befunge_program * bf) {
	bf->ip.row= (bf->ip.row + bf->dir.dy + PROGRAM_ROWS) % PROGRAM_ROWS;
	bf->ip.col= (bf->ip.col + bf->dir.dx + PROGRAM_COLS) % PROGRAM_COLS;
}

/*
 * Executes a loaded Befunge program
 * The only way to exit is through the '@' character in the Befunge code
 */
void bfg_run(struct befunge_program * bf) {
	while(1) {
		bfg_process(bf); /* process the character at the current instruction pointer */
		bfg_moveip(bf); /* move the instruction pointer to the next cell */
	}
}

/* 
 * Processes a single character instruction 
 */
void bfg_process(struct befunge_program * bf) {
	struct befunge_stack * bs= &bf->stack; /* the program's stack */
	char inst= bf->code[bf->ip.row][bf->ip.col]; /* the current instruction */
	int a, b, v;
	char c;
	/* in command mode, characters are treated as commands and executed */
	if(bf->command_mode) {
		/* if in range '0'..'9', push the actual decimal value onto the stack */
		if(inst >= '0' && inst <= '9') {
			bfs_push(bs, inst - '0');
		} else {
			switch(inst) {
				case '+': /* pop 2 and push their sum */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, b + a);
					break;
				case '-': /* pop 2 and push their difference */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, b - a);
					break;
				case '*': /* pop 2 and push their product */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, b * a);
					break;
				case '/': /* pop 2 and push their quotient */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, b / a); /* TODO: ask user if a is 0? */
					break;
				case '%': /* pop 2 and push their modulus */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, b % a); /* TODO: ask user if a is 0? */
					break;
				case '!': /* pop 1 and push 1 if it is 0 else 0 (not operator) */
					a= bfs_pop(bs);
					bfs_push(bs, !a);
					break;
				case '`': /* pop 2 and push 1 if the 2nd is greater, else 0 */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, b > a); 
					break;
				case '^': /* change direction to up */
					dirset(&bf->dir, UP);
					break;
				case '>': /* change direction to right */
					dirset(&bf->dir, RIGHT);
					break;
				case '<': /* change direction to left */
					dirset(&bf->dir, LEFT);
					break;
				case 'v': /* change direction to down */
					dirset(&bf->dir, DOWN);
					break;
				case '?': /* change to a random direction */
					dirset(&bf->dir, rand() % 4);
					break;
				case '_': /* pop 1 and go right if 0 else left */
					a= bfs_pop(bs);
					dirset(&bf->dir, a ? LEFT : RIGHT);
					break;
				case '|': /* pop 1 and go down if 0 else up */
					a= bfs_pop(bs);
					dirset(&bf->dir, a ? UP : DOWN);
					break;
				case '"': /* begin string mode */
					bf->command_mode= 0;
					break;
				case ':': /* duplicate the top item on the stack */
					a= bfs_peek(bs);
					bfs_push(bs, a);
					break;
				case '\\':  /* swap the top 2 items on the stack */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					bfs_push(bs, a);
					bfs_push(bs, b);
					break;
				case '$': /* discard the top item from the stack */
					bfs_pop(bs);
					break;
				case '.': /* pop 1 and print it as an integer */
					a= bfs_pop(bs);
					printf("%d", a);
					break;
				case ',': /* pop 1 and print it as a character */
					a= bfs_pop(bs);
					printf("%c", a);
					break;
				case '#': /* skip the next cell */
					/* move to the next one so the control loop moves the cell we're skipping to */
					bfg_moveip(bf); 
					break;
				case 'g': /* pop 2 and push the value at that location */
					/* if out of bounds, push 0 */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					if(b >= PROGRAM_COLS || a >= PROGRAM_ROWS) {
						bfs_push(bs, 0);
					} else {
						bfs_push(bs, bf->code[b][a]);
					}
					break;
				case 'p': /* pop 3, store the value of the third at the location of the first 2 */
					/* if out of bounds, do nothing */
					a= bfs_pop(bs);
					b= bfs_pop(bs);
					v= bfs_pop(bs);
					if(b < PROGRAM_COLS && a < PROGRAM_ROWS) {
						bf->code[b][a]= v;
					}
					break;
				case '&': /* ask the user for an integer */
					scanf("%d", &a);
					bfs_push(bs, a);
					break;
				case '~': /* ask the user for a character */
					scanf("%c", &c);
					bfs_push(bs, c);
					break;
				case '@': /* end the program */
					exit(EXIT_SUCCESS);
					break;
			}
		}
	} else { /* string mode */
		if(inst == '"') { /* end string mode with a quote */
			bf->command_mode= 1;
		} else {
			bfs_push(bs, inst); /* push the character */
		}
	}
}

/*
 * Destroys this struct and frees all memory associated with it 
 */
void bfg_destroy(struct befunge_program * bf) {
	bfs_destroy(&bf->stack);
}
