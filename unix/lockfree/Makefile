SRC = LockfreeQueue.cpp
INC = LockfreeQueue.h
CC = g++
CFLAG = -Wall -g

TARG = TEST

OBJ := $(SRC: %.o=%.cpp)

$(OBJ) : $(SRC)
	$(CC) $(CFLAG) -c $^

$(TARG): $(OBJ)
	$(CC) $(CFLAG) -o $@ $^

.PHONY : clean
clean :
	rm -f $(OBJ) $(TARG) *.o *.out

