SRCDIR=src
BINDIR=bin
INCDIR=include
OBJDIR=obj

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)


TARGET_1=quick_sort

_HEADER=quick_sort.h
_OBJ1=quick_sort.o test_quick_sort.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ1=$(patsubst %,$(OBJDIR)/%,$(_OBJ1))


################# TARGETS #####################

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<


$(TARGET_1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ 


clean:
	rm -f *~ *.out
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*
	rm -f $(SRCDIR)/*~
	rm -f $(INCDIR)/*~
