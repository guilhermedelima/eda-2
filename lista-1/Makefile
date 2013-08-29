CC=gcc
CFLAGS=-W -Wall

INCDIR=include
SRCDIR=src
BINDIR=bin

all:
	$(CC) $(CFLAGS) -o $(BINDIR)/seq_search_pk seq_search_pk.c

clean:
	rm -f *~ *.out
	rm -f $(BINDIR)/*

# EXERCÍCIO 5
ringlist:
	$(CC) $(CFLAGS) -I $(INCDIR) -o $(BINDIR)/ringlist $(SRCDIR)/node.c $(SRCDIR)/ringlist.c $(SRCDIR)/test_ringlist.c