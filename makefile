# makefile
# for StickyParticles

CC = gcc
CPP = g++
CFLAGS = -std=c99 -Wall -g
CPPFLAGS = -ansi -Wall -g
LIBS = -lm

all: sticky.x

sticky.x: circle.o game.o geometry.o main.o rectangle.o vector.o
	$(CPP) $(LIBS) $^ -o $@

circle.o: circle.c circle.h constants.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

game.o: game.c circle.h constants.h game.h geometry.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

geometry.o: geometry.c circle.h geometry.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp game.h
	$(CPP) $(CPPFLAGS) -c $< -o $@

rectangle.o: rectangle.c constants.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.x
