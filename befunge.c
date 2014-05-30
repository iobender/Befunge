#include <stdio.h>
#include <string.h>
#include "befunge.h"
#include "befunge_stack.h"

void dirset(struct delta * dir, enum EDIRECTION where) {
	switch(where) {
		case UP:
			dir->dx= 0;
			dir->dy= -1;
			break;
		case DOWN:
			dir->dx= 0;
			dir->dy= 1;
			break;
		case LEFT:
			dir->dx= -1;
			dir->dy= 0;
			break;
		case RIGHT:
			dir->dx= 1;
			dir->dy= 0;
			break;
	}
}

int bf_init(struct befunge_program * bf) {
	if(!bfs_init(&bf->stack)) return 0;
	bf->ip.row= 0;
	bf->ip.col= 0;
	dirset(&bf->dir, RIGHT);
	return 1;
}

int bf_load_code(struct befunge_program * bf, FILE * file) {
	int row, col;
	for(row= 0; row < PROGRAM_ROWS; row++) {
		for(col= 0; col < PROGRAM_COLS; col++) {
			bf->code[row][col]= ' ';
		}
	}
	for(row= 0; row < PROGRAM_ROWS; row++) {
		/* TODO: fix number of chars read */
		if(fgets(bf->code[row], PROGRAM_COLS, file) == NULL) break;
		*strchr(bf->code[row], '\n')= ' ';
		bf->code[row][strlen(bf->code[row])]= ' ';
	}
}

void bf_run(struct befunge_program * bf) {
	printf("%c\n", bf->code[bf->ip.row][bf->ip.col]);
}

void bf_destroy(struct befunge_program * bf) {
	bfs_destroy(&bf->stack);
}
