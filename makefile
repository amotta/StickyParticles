# makefile

CC = gcc
FLAGS = -Wall

all: sticky.x

sticky.x: circle.o game.o  main.o vector.o
	$(CC) $(FLAGS) $^ -o $@

circle.o: circle.c circle.h constants.h rectangle.h vector.h
	$(CC) $(FLAGS) -c $< -o $@

game.o: game.c game.h
	$(CC) $(FLAGS) -c $< -o $@

main.o: main.c game.h
	$(CC) $(FLAGS) -c $< -o $@

vector.o: vector.c vector.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm *.o *.x
