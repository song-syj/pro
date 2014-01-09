CC = gcc
CFLAGS = -I./lib -g -Wall
OBJ = server_cmd.o sock_core.o \
	client_cmd.o client_data.o \
	server_data.o 

TARGET = SERVER_CMD CLIENT_CMD \
		CLIENT_DATA SERVER_DATA

ALL: $(TARGET)

SERVER_CMD: server_cmd.o sock_core.o
	$(CC) $(CFLAGS) -o $@ $^
CLIENT_CMD: client_cmd.o sock_core.o
	$(CC) $(CFLAGS) -o $@ $^
SERVER_DATA: server_data.o sock_core.o
	$(CC) $(CFLAGS) -o $@ $^
CLIENT_DATA: client_data.o sock_core.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
	rm $(TARGET) $(OBJ)

