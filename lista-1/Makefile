CC=gcc
CFLAGS=-W -Wall

INCDIR=include
SRCDIR=src
BINDIR=bin

all: pksearch ringlist

clean:
	rm -f *~ *.out
	rm -f $(BINDIR)/*

# EXERCÍCIO 4
pksearch:
	$(CC) $(CFLAGS) -I $(INCDIR) -o $(BINDIR)/seq_search_pk $(SRCDIR)/seq_search_pk.c

# EXERCÍCIO 5
ringlist:
	$(CC) $(CFLAGS) -I $(INCDIR) -o $(BINDIR)/ringlist $(SRCDIR)/node.c $(SRCDIR)/ringlist.c $(SRCDIR)/test_ringlist.c
