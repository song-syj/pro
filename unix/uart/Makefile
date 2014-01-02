SOURCE += main.c
SOURCE += uart.c

#CFLAGS += -g
CFLAGS +=
CC = arm-none-linux-gnueabi-gcc
#CC = gcc
OBJECTS :=$(SOURCE:%.c=%.o)

TARGET = UART

TARGET: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
clean:
	rm -f $(TARGET) *.o *~
