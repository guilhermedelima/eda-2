INCDIR=include
SRCDIR=src
BINDIR=bin
OBJDIR=obj

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)

TARGET=seq_search_pk

_HEADER=seq_search_pk.h
_OBJ=seq_search_pk.o
_SRC=seq_search_pk.c

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))
SRC=$(patsubst %,$(SRCDIR)/%,$(_SRC))

all: $(TARGET) ringlist

$(OBJDIR)/%.o: $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

# EXERCÍCIO 5
ringlist:
	$(CC) $(CFLAGS) -o $(BINDIR)/ringlist $(SRCDIR)/ringlist.c $(SRCDIR)/test_ringlist.c

clean:
	rm -f *~ *.out
	rm -f $(BINDIR)/*
	rm -f $(OBJDIR)/*
	rm -f $(SRCDIR)/*~
	rm -f $(INCDIR)/*~
