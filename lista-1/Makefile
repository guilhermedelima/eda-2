INCDIR=include
SRCDIR=src
BINDIR=bin
OBJDIR=obj
LOGDIR=log

CC=gcc
CFLAGS=-W -Wall -Wno-sign-compare
CINCLUDE=-I $(INCDIR)

TARGET_EX1=index_search

_HEADER=index_search.h
_OBJ=index_search.o test_index_search.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: $(TARGET_EX1) ringlist_menu ringlist

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(CINCLUDE) -c -o $@ $<

# EXERCÍCIO 4 
$(TARGET_EX1): $(OBJ)
	$(CC) $(CFLAGS) $(CINCLUDE) -o $(BINDIR)/$@ $^

# EXERCÍCIO 5 (com menu)
ringlist_menu:
	$(CC) $(CFLAGS) $(CINCLUDE) -o $(BINDIR)/ringlist_menu $(SRCDIR)/ringlist.c $(SRCDIR)/test_ringlist_menu.c -lrt

# EXERCÍCIO 6
ringlist:
	$(CC) $(CFLAGS) $(CINCLUDE) -o $(BINDIR)/ringlist $(SRCDIR)/ringlist.c $(SRCDIR)/test_ringlist.c -lrt

clean:
	rm -f *~ *.out
	rm -f $(BINDIR)/*
	rm -f $(OBJDIR)/*
	rm -f $(LOGDIR)/*
	rm -f $(SRCDIR)/*~
	rm -f $(INCDIR)/*~
