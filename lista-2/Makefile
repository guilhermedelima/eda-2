SRCDIR=src
BINDIR=bin
INCDIR=include
OBJDIR=obj

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)


TARGET_1=quick_sort
TARGET_2=radix_sort

_HEADER=quick_sort.h radix_sort.h
_OBJ1=quick_sort.o test_quick_sort.o
_OBJ2=radix_sort.o test_radix_sort.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ1=$(patsubst %,$(OBJDIR)/%,$(_OBJ1))
OBJ2=$(patsubst %,$(OBJDIR)/%,$(_OBJ2))


################# TARGETS #####################

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<


$(TARGET_1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ 


$(TARGET_2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ 


clean:
	rm -f *~ *.out
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*
	rm -f $(SRCDIR)/*~
	rm -f $(INCDIR)/*~
