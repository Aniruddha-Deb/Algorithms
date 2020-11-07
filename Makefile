CC = gcc

CFLAGS = -std=c99 -Wall -DDEBUG
LDFLAGS = -lSDL2 -lSDL2_ttf -lm

OBJDIR = obj
SRCDIR = src
EXECDIR = bin

PROG := None
DEBUG := 0

_DEPS = util/ds.h util/logger.h util/intgen.h ui/SDL_util.h ui/plotter.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = util/logger.o util/ds.o util/intgen.o ui/SDL_util.o ui/plotter.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

default: $(OBJDIR)/$(PROG).o $(OBJ)
	$(CC) $(OBJ) $(patsubst %,$(OBJDIR)/%.o,$(PROG)) -o $(patsubst %,$(EXECDIR)/%,$(PROG)) $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(EXECDIR)/*
