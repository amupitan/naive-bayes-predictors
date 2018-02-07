CC = g++
DEBUG = -ggdb
LFLAGS = -Wall -Werror
CFLAGS = $(LFLAGS) $(DEBUG) -std=c++11

default: all

main.o: newsgroup.h main.cpp main.h document.h
	$(CC) $(CFLAGS) -c main.cpp

document.o: document.h document.cpp
	$(CC) $(CFLAGS) -c document.cpp

newsgroup.o: newsgroup.cpp newsgroup.h
	$(CC) $(CFLAGS) -c newsgroup.cpp

all: document.o newsgroup.o main.o
	$(CC) $(CFLAGS) document.o main.o newsgroup.o -o ml

clean:
	rm -rf *.o ml
