# makefile

CC = gcc
FLAGS = -Wall

all: sticky.x

sticky.x: main.o game.o
	$(CC) $(FLAGS) $^ -o $@

main.o: main.c
	$(CC) $(FLAGS) -c $< -o $@

game.o: game.c game.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm *.o *.x
