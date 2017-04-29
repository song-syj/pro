
EXECUTABLE := BASE64_SERVER BASE64_CLIENT

LIBS := -lpthread -lz -levent -lssl -lcrypto -lglog

INCLUDE=  -I/usr/include
CFLAGS := -g -Wall -DDEBUG $(INCLUDE)

CXXFLAGS := $(CFLAGS) -std=c++11

RMS := rm -f

SOURCE := $(wildcard *.c) $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SOURCE)))

everything : $(EXECUTABLE)

clean : 
	@$(RMS)   $(OBJS) $(EXECUTABLE)

all: $(EXECUTABLE)

#$(EXECUTABLE) : $(OBJS)
#	g++ $(CXXFLAGS) $(LIBS) -o $(EXECUTABLE) $(OBJS) $(LIBS)

BASE64_SERVER: libevent_server.o pdu.o
	g++ $(CXXFLAGS) $(LIBS) -o $@ $^ $(LIBS)

BASE64_CLIENT: libevent_client.o pdu.o
	g++ $(CXXFLAGS) $(LIBS) -o $@ $^ $(LIBS)
