# makefile

CC = gcc
FLAGS = -Wall -pedantic

all: sticky.x

sticky.x: main.o
	$(CC) $(FLAGS) $< -o $@

main.o: main.c
	$(CC) $(FLAGS) -c $< -o $@
