SHELL := /bin/bash

CC = g++
FLAGS = -std=c++14 -lpthread
OBJS = busy_wait.o busy_wait_plus.o mutex.o mutex_plus.o
n = 1000000000
LOOPS = 5

all : $(OBJS)

busy_wait.o : busy_wait.cpp
	$(CC) busy_wait.cpp -o busy_wait.out  $(FLAGS)

busy_wait_plus.o : busy_wait_plus.cpp
	$(CC) busy_wait_plus.cpp -o busy_wait_plus.out  $(FLAGS)

mutex.o : mutex.cpp
	$(CC) mutex.cpp -o mutex.out  $(FLAGS)

mutex_plus.o : mutex_plus.cpp
	$(CC) mutex_plus.cpp -o mutex_plus.out  $(FLAGS)

run : 
	make clean 
	make all
	make run_busy_wait
	make run_busy_wait_plus
	make run_mutex
	make run_mutex_plus

run_busy_wait:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 1 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 2 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 3 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 4 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 6 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 8 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 16 -f busy_wait.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait.out -n $(n) -t 32 -f busy_wait.txt; done

run_busy_wait_plus:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 1 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 2 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 3 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 4 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 6 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 8 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 16 -f busy_wait_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./busy_wait_plus.out -n $(n) -t 32 -f busy_wait_plus.txt; done

run_mutex:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 1 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 2 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 3 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 4 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 6 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 8 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 16 -f mutex.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex.out -n $(n) -t 32 -f mutex.txt; done

run_mutex_plus:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 1 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 2 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 3 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 4 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 6 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 8 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 16 -f mutex_plus.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./mutex_plus.out -n $(n) -t 32 -f mutex_plus.txt; done

clean:
	rm -rf *.out *.txt