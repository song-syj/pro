SRC = mm.c memlib.c tst.c
INC = 
CC = gcc
CFLAG = -Wall -g

TARG = TEST
OBJ :=$(SRC:%.c=%.o)

ALL:$(TARG)

$(TARG): $(OBJ)
	$(CC) $(CFLAG) -o $@ $^ 


$(OBJ) : $(SRC)
	$(CC) $(CFLAG) -c $^ 

.PHONY : clean
clean :
	rm -f $(OBJ) $(TARG) *.o *.out

