INCDIR=include
BINDIR=bin
OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)



TARGET_1=merge_sort

_HEADER=merge_sort.h
_OBJ1=merge_sort.o test_merge_sort.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ1=$(patsubst %,$(OBJDIR)/%,$(_OBJ1))

######### TARGETS ##########

all: $(TARGET_1)


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


