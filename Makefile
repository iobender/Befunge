all:
	@gcc main.c befunge_stack.c

clean:
	@rm -vf *.o a.exe* .*sw*

