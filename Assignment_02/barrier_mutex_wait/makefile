SHELL := /bin/bash

CC = g++
FLAGS = -std=c++14 -lpthread
OBJS = barrier_mutex_wait.o process_data.o
n = 1000000000
LOOPS = 5

all : $(OBJS)

barrier_mutex_wait.o : barrier_mutex_wait.cpp
	$(CC) barrier_mutex_wait.cpp -o barrier_mutex_wait.out  $(FLAGS)

process_data.o : process_data.cpp
	$(CC) process_data.cpp -o process_data.out  $(FLAGS)

run : 
	make clean 
	make all
	make run_barrier_mutex_wait
	make run_process_data

run_barrier_mutex_wait:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 1 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 2 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 3 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 4 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 6 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 8 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 16 -f barrier_mutex_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./barrier_mutex_wait.out -n $(n) -t 32 -f barrier_mutex_wait.txt; done

run_process_data:
	./process_data.out -f barrier_mutex_wait.txt -o barrier_mutex_wait_final.txt

clean:
	rm -rf *.out *.txt