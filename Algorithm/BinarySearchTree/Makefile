main:main.o binarysearchtree.o
	gcc main.o binarysearchtree.o -o main
binarysearchtree.o: binarysearchtree.h  binarysearchtree.c 
	gcc -c -g  binarysearchtree.c
main.o: main.c binarysearchtree.h
	gcc -c -g main.c
clean:
	-rm main *.o;
.PHONY : clean
