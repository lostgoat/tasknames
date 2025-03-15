# Simple app that generates threads with long names

threadnames : main.c Makefile
	gcc -g -O0 -Wall main.c -pthread -o threadnames

clean:
	rm threadnames