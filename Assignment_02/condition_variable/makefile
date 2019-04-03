SHELL := /bin/bash

CC = g++
FLAGS = -std=c++14 -lpthread
OBJS = condition_var.o process_data.o
n = 1000000000
LOOPS = 5

all : $(OBJS)

condition_var.o : condition_var.cpp
	$(CC) condition_var.cpp -o condition_var.out  $(FLAGS)

process_data.o : process_data.cpp
	$(CC) process_data.cpp -o process_data.out  $(FLAGS)

run : 
	make clean 
	make all
	make run_condition_var
	make run_process_data

run_condition_var:
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 1 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 2 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 3 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 4 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 6 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 8 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 16 -f condition_var.txt; done
	for ((i=1; i <= ${LOOPS}; ++i)) do ./condition_var.out -n $(n) -t 32 -f condition_var.txt; done

run_process_data:
	./process_data.out -f condition_var.txt -o condition_var_final.txt

clean:
	rm -rf *.out *.txt