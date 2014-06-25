#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "befunge.h"
#include "befunge_stack.h"

int main(int argc, char ** argv) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s code.bf\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	FILE * file= fopen(argv[1], "r");
	if(!file) {
		fprintf(stderr, "Error opening file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));
	struct befunge_program bf;
	bfg_init(&bf);
	bfg_load_code(&bf, file);
	bfg_run(&bf);
	/* execution will only halt in when an '@' is reached in the Befunge code */
	return 0;
}
