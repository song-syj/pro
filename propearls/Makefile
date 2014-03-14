SOURCE = test_random.cpp random.cpp 
CC = g++
HEADER =
CFLAG = -I./lib -g -Wall

OBJ = $(SOURCE:.cpp=.o)

TARGET = TEST

ALL: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(TARGET) 

$(OBJ): $(SOURCE)
	$(CC) $(CFLAG) -c $(SOURCE)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) 
