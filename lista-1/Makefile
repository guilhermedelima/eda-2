INCDIR=include
SRCDIR=src
BINDIR=bin
OBJDIR=obj

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)

TARGET_EX1=index_search

_HEADER=index_search.h
_OBJ=index_search.o test_index_search.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: $(TARGET_EX1) ringlist

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET_EX1): $(OBJ)
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
