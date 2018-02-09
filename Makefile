CC = g++
DEBUG = -ggdb
LFLAGS = -Wall -Werror
CFLAGS = $(LFLAGS) $(DEBUG) -std=c++11

default: all

check: check_files.py
	python check_files.py

main.o: newsgroup.h main.cpp naive_bayes.h document.h utils.h
	$(CC) $(CFLAGS) -c main.cpp

utils.o: utils.h utils.cpp
	$(CC) $(CFLAGS) -c utils.cpp

newsgroup.o: newsgroup.cpp newsgroup.h
	$(CC) $(CFLAGS) -c newsgroup.cpp

naive_bayes.o: naive_bayes.cpp naive_bayes.h
	$(CC) $(CFLAGS) -c naive_bayes.cpp

parse_data.o: parse_data.cpp parse_data.h
	$(CC) $(CFLAGS) -c parse_data.cpp

all: check newsgroup.o main.o utils.o naive_bayes.o parse_data.o
	$(CC) $(CFLAGS) main.o newsgroup.o utils.o naive_bayes.o parse_data.o -o naive_bayes
	@echo run ./naive_bayes to run the classification program 

clean:
	rm -rf *.o naive_bayes
