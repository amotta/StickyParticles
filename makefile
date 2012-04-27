# DO NOT DELETE
CC = gcc
CPPC = g++
DEPFILE = dependencies
SRC = circle.c controlui.cpp emitter.c emitterset.c file.c game.c \
gameui.c geometry.c graphics.c group.c groupset.c main.cpp \
particle.c rectangle.c vector.c
OPTS = -Wall -g

#detect OS
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
LIBS = -framework GLUI -framework GLUT -framework OpenGL
endif

ifeq ($(UNAME), Linux)
LIBS = -lglui -lGL -lGLU
endif

TEMP = $(SRC:.c=.o)
OBS = $(TEMP:.cpp=.o)

all: sticky.x

sticky.x: $(OBS)
	$(CPPC) $(OPTS) $(OBS) $(LIBS) -o $@

clean:
	@rm -f *.o *.x
	@rm -f $(DEPFILE)

depend:
	@$(CC) -MM $(OPTS) $(SRC) | egrep -v "/usr/include" > $(DEPFILE)

sinclude $(DEPFILE)
