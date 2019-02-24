SHELL := /bin/bash

CC = g++
FLAGS = -std=c++14 -lpthread
OBJS = semaphore.o process_data.o
n = 1000000000
LOOPS = 5

all : $(OBJS)

semaphore.o : semaphore.cpp
	$(CC) semaphore.cpp -o semaphore.out  $(FLAGS)

process_data.o : process_data.cpp
	$(CC) process_data.cpp -o process_data.out  $(FLAGS)

run : 
	make clean 
	make all
	make run_semaphore
	make run_process_data

run_semaphore:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 1 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 2 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 3 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 4 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 6 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 8 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 16 -f semaphore.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./semaphore.out -n $(n) -t 32 -f semaphore.txt; done

run_process_data:
	./process_data.out -f semaphore.txt -o semaphore_final.txt

clean:
	rm -rf *.out *.txt