# DO NOT DELETE

DEPFILE = dependencies

SRC = circle.c controlui.cpp emitter.c emitterset.c file.c game.c \
gameui.c geometry.c graphics.c group.c groupset.c main.cpp \
particle.c particleset.c rectangle.c vector.c

OBS = $(SRC:.c=.o)

all: sticky.x

sticky.x: $(OBS)
	g++ $(OFILES) -o $@

depend:
	@rm -f $(DEPFILE)
	@touch $(DEPFILE)
	@makedepend -Y -f $(DEPFILE) $(SRC)

sinclude $(DEPFILE)
