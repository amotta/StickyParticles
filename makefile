# makefile

CC = gcc
CPP = g++
CFLAGS = -std=c99 -Wall -g
CPPFLAGS = -ansi

all: sticky.x

sticky.x: circle.o game.o main.o rectangle.o vector.o
	$(CC) $^ -o $@

circle.o: circle.c circle.h constants.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

game.o: game.c constants.h game.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp game.h
	$(CPP) $(CPPFLAGS) -c $< -o $@

rectangle.o: rectangle.c constants.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.x
