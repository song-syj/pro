main:main.o stack.o maze.o
	$(CC) $^ $(OUTPUT_OPTION) $@ 
main.o:main.c main.h stack.h maze.h
	$(CC) $(CFLAGS) -c $<
stack.o:stack.c stack.h main.h
	$(CC) $(CFLAGS) -c $<
maze.o:maze.c maze.h main.h
	$(CC) $(CFLAGS) -c $<
CC=gcc
CFLAGS=
CPPFLAGS =-Iinclude
OUTPUT_OPTION=-o
clean:
	-rm main *.o
.PhONY: clean
