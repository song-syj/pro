all: textfilewrite text2bin binfileread
textfilewrite: textfilewrite.c
	gcc textfilewrite.c -o textfilewrite
text2bin: text2bin.c
	gcc text2bin.c -o text2bin
binfileread: binfileread.c
	gcc binfileread.c -o binfileread
clean:
	@echo "cleaning project"
	-rm text2bin textfilewrite binfileread
	@echo "clean completed"

