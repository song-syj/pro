SOURCE = 46.cpp
CC = g++
CFLAG = -Wall -g -std=c++11

TARG = TEST
OBJ = $(SOURCE:.cpp=.o)

ALL: $(TARG)

$(TARG): $(OBJ)
	$(CC) $(CFLAG) -o  $@ $^ 

$(OBJ): $(SOURCE)
	$(CC) $(CFLAG) -c $^ 

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARG) *.o


