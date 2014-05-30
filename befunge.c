#include <stdio.h>
#include <string.h>
#include "befunge.h"
#include "befunge_stack.h"

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
	/* printf("read %d rows\n", row); */
}

