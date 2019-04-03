SHELL := /bin/bash

CC = g++
FLAGS = -std=c++14 -lpthread
OBJS = kilo.o

all : 
	make clean 
	make $(OBJS)
	make run

kilo.o : kilo.cpp
	$(CC) kilo.cpp -o kilo.out  $(FLAGS)

run : 
	make run_kilo

run_kilo:
	 ./kilo.out

clean:
	rm -rf *.out *.txt