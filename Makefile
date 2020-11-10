CC = gcc

CFLAGS = -std=c99 -Wall -O3 -DDEBUG
LDFLAGS = -O3 -lSDL2 -lSDL2_ttf -lm

OBJDIR = obj
SRCDIR = src
EXECDIR = bin

PROG := None
DEBUG := 0

_DEPS = util/ds.h util/gen.h util/logger.h util/intgen.h ui/SDL_util.h ui/plotter.h sorts/sorts.h ui/color.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = util/logger.o util/gen.o util/ds.o util/intgen.o ui/SDL_util.o ui/plotter.o sorts/sorts.o ui/color.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

default: $(OBJDIR)/$(PROG).o $(OBJ)
	$(CC) $(OBJ) $(patsubst %,$(OBJDIR)/%.o,$(PROG)) -o $(patsubst %,$(EXECDIR)/%,$(PROG)) $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(EXECDIR)/*
