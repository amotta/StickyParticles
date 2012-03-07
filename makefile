# makefile

CC = gcc
FLAGS = -Wall

all: sticky.x

sticky.x: game.o geometry.o main.o vector.o
	$(CC) $(FLAGS) $^ -o $@

game.o: game.c game.h
	$(CC) $(FLAGS) -c $< -o $@

geometry.o: geometry.c geometry.h
	$(CC) $(FLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(FLAGS) -c $< -o $@

vector.o: vector.c vector.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm *.o *.x
