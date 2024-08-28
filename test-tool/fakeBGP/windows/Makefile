SRCS = $(shell find src/ -type f -name '*.cpp')
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
#CC = g++-4.8
CC = g++

all: fakebgp

fakebgp: $(OBJS)
	$(CC) -o $@ $(OBJS) -lboost_system

$(OBJS): %.o : %.cpp
	$(CC) -o $@ -g -std=c++11 -c $<

clean:
	rm fakebgp $(OBJS)
