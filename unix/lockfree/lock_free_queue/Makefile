SRC = main.cpp
INC = lock_free_stack.h
CC = g++
CFLAG = -Wall -g -std=c++11 -pthread

TARG = TEST
OBJ :=$(SRC:%.cpp=%.o)

ALL:$(TARG)

$(TARG): $(OBJ)
	$(CC) $(CFLAG) -o $@ $^ -lpthread


$(OBJ) : $(SRC)
	$(CC) $(CFLAG) -c $^ 

.PHONY : clean
clean :
	rm -f $(OBJ) $(TARG) *.o *.out

