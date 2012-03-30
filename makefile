# makefile
# for StickyParticles

CC = gcc
CPP = g++
CFLAGS = -std=c99 -Wall -g
CPPFLAGS = -ansi -Wall -g
LIBS = -lm -framework GLUI -framework GLUT

all: sticky.x

sticky.x: circle.o controlui.o game.o gameui.o geometry.o main.o rectangle.o vector.o
	$(CPP) $(LIBS) $^ -o $@

circle.o: circle.c circle.h constants.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

controlui.o: controlui.cpp controlui.h
	$(CPP) -c $< -o $@

game.o: game.c circle.h constants.h game.h geometry.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

gameui.o: gameui.c gameui.h
	$(CC) $(CFLAGS) -c $< -o $@

geometry.o: geometry.c circle.h geometry.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp controlui.h
	$(CPP) $(CPPFLAGS) -c $< -o $@

rectangle.o: rectangle.c constants.h rectangle.h vector.h
	$(CC) $(CFLAGS) -c $< -o $@

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.x
