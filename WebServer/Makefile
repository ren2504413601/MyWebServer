SOURCE  := $(wildcard *.cpp)
OBJS    := $(patsubst %.cpp,%.o,$(SOURCE))
TARGET  := main
#Test object
TESTCLIENT := stress_client
CC      := g++
CFLAGS  := -std=c++11 -g -Wall -O3 -D_PTHREADS
CXXFLAGS:= $(CFLAGS)
LIBS    := -lpthread
all : $(TARGET) $(TESTCLIENT)


$(TARGET) : $(OBJS) main.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

stress_client : stress_client.o
	$(CC) $(CXXFLAGS) -o stress_client stress_client.o

stress_client.o : test/stress_client.cpp
	$(CC) $(CXXFLAGS) -c test/stress_client.cpp -o stress_client.o

clean :
	rm -rf *.o $(TARGET) stress_client.o stress_client
