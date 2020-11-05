CC = gcc

CFLAGS = -std=c99 -Wall -DDEBUG
LDFLAGS = -lm

OBJDIR = obj

DEPS = src/util/ds.h src/util/logger.h src/util/intgen.h

_OBJ = logger.o ds.o intgen.o intgentest.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: src/util/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

intgentest: $(OBJ) 
	$(CC) $(OBJ) -o bin/intgentest $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/*
	rm -f exec/*
