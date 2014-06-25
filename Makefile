all: bfg
	
bfg: main.o befunge.o befunge_stack.o
	gcc -o bfg main.o befunge.o befunge_stack.o

main.o: main.c befunge.h
	gcc -c main.c

befunge.o: befunge.c befunge.h befunge_stack.h
	gcc -c befunge.c

befunge_stack.o: befunge_stack.c befunge_stack.h
	gcc -c befunge_stack.c

clean:
	rm -vf *.o bfg

