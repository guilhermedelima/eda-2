INCDIR=include
BINDIR=bin
OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)



TARGET_1=merge_sort
TARGET_2=bucket_sort

_HEADER=merge_sort.h bucket_sort.h
_OBJ1=merge_sort.o test_merge_sort.o
_OBJ2=bucket_sort.o test_bucket_sort.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ1=$(patsubst %,$(OBJDIR)/%,$(_OBJ1))
OBJ2=$(patsubst %,$(OBJDIR)/%,$(_OBJ2))

######### TARGETS ##########

all: $(TARGET_1) $(TARGET_2)


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


