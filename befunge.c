#include <stdio.h>
#include <stdlib.h>
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
	return 0;
}

void bf_moveip(struct befunge_program * bf) {
	bf->ip.row= (bf->ip.row + bf->dir.dy + PROGRAM_ROWS) % PROGRAM_ROWS;
	bf->ip.col= (bf->ip.col + bf->dir.dx + PROGRAM_COLS) % PROGRAM_COLS;
}

void bf_run(struct befunge_program * bf) {
	while(1) {
		bf_process(bf);
		bf_moveip(bf);
	}
}

void bf_process(struct befunge_program * bf) {
	struct befunge_stack * bs= &bf->stack;
	char inst= bf->code[bf->ip.row][bf->ip.col];
	int a, b, v;
	char c;
	printf("[%c]\n", inst);
	if(inst >= '0' && inst <= '9') {
		bfs_push(bs, inst - '0');
	} else {
		switch(inst) {
			case '+':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, b + a);
				break;
			case '-':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, b - a);
				break;
			case '*':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, b * a);
				break;
			case '/':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, b / a); /* TODO: ask user if a is 0? */
				break;
			case '%':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, b % a); /* TODO: ask user if a is 0? */
				break;
			case '!':
				a= bfs_pop(bs);
				bfs_push(bs, !a);
				break;
			case '`':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, b > a); 
				break;
			case '^':
				dirset(&bf->dir, UP);
				break;
			case '>':
				dirset(&bf->dir, RIGHT);
				break;
			case '<':
				dirset(&bf->dir, LEFT);
				break;
			case 'v':
				dirset(&bf->dir, DOWN);
				break;
			case '?': /* TODO: test and fix this */
				srand(78); 
				dirset(&bf->dir, rand() % 4);
				break;
			case '_':
				a= bfs_pop(bs);
				dirset(&bf->dir, a ? LEFT : RIGHT);
				break;
			case '|':
				a= bfs_pop(bs);
				dirset(&bf->dir, a ? UP : DOWN);
				break;
			case '"':
				/* not yet implemented */
				break;
			case ':':
				a= bfs_peek(bs);
				bfs_push(bs, a);
				break;
			case '\\': 
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, a);
				bfs_push(bs, b);
				break;
			case '$':
				bfs_pop(bs);
				break;
			case '.':
				a= bfs_pop(bs);
				printf("%d\n", a);
				break;
			case ',':
				a= bfs_pop(bs);
				printf("%c\n", a);
				break;
			case '#':
				bf_moveip(bf);
				break;
			case 'g':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				bfs_push(bs, bf->code[b][a]);
				break;
			case 'p':
				a= bfs_pop(bs);
				b= bfs_pop(bs);
				v= bfs_pop(bs);
				bf->code[b][a]= v;
				break;
			case '&':
				scanf("%d", &a);
				printf("entered %d\n", a);
				bfs_push(bs, a);
				break;
			case '~':
				scanf("%c", &c);
				bfs_push(bs, c);
				break;
			case '@': 
				exit(EXIT_SUCCESS);
				break;
		}
	}
}

void bf_destroy(struct befunge_program * bf) {
	bfs_destroy(&bf->stack);
}
