# DO NOT DELETE

DEPFILE = dependencies
SRC = circle.c controlui.cpp emitter.c emitterset.c file.c game.c \
gameui.c geometry.c graphics.c group.c groupset.c main.cpp \
particle.c rectangle.c vector.c
OPTS = -g

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
	g++ $(OPTS) $(OBS) $(LIBS) -o $@

clean:
	@rm -f *.o *.x
	@rm -f $(DEPFILE)

depend:
	@rm -f $(DEPFILE)
	@touch $(DEPFILE)
	@makedepend -Y -f $(DEPFILE) -- $(OPTS) -- $(SRC)

sinclude $(DEPFILE)
