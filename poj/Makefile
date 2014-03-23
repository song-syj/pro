SOURCE = 3274.c
CC = gcc
HEADER =
CFLAG = -I./lib -g -Wall

OBJ = $(SOURCE:.c=.o)

TARGET = TEST

ALL: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(TARGET) 

$(OBJ): $(SOURCE)
	$(CC) $(CFLAG) -c $(SOURCE)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) 
