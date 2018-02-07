CC = g++
DEBUG = -ggdb
LFLAGS = -Wall -Werror
CFLAGS = $(LFLAGS) $(DEBUG) -std=c++11

default: all

main.o: newsgroup.h main.cpp naive_bayes.h document.h utils.h
	$(CC) $(CFLAGS) -c main.cpp

document.o: document.h document.cpp
	$(CC) $(CFLAGS) -c document.cpp

utils.o: utils.h utils.cpp
	$(CC) $(CFLAGS) -c utils.cpp

newsgroup.o: newsgroup.cpp newsgroup.h
	$(CC) $(CFLAGS) -c newsgroup.cpp

naive_bayes.o: naive_bayes.cpp naive_bayes.h
	$(CC) $(CFLAGS) -c naive_bayes.cpp

all: document.o newsgroup.o main.o utils.o naive_bayes.o
	$(CC) $(CFLAGS) document.o main.o newsgroup.o utils.o naive_bayes.o -o ml

clean:
	rm -rf *.o ml
