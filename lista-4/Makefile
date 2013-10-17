INCDIR=include
BINDIR=bin
OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)

TARGET=red_black_tree


_HEADER=red_black_tree.h
_OBJ=red_black_tree.o test_red_black_tree.o

HEADER=$(patsubst %,$(INCDIR)/%,$(_HEADER))
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))


######## TARGETS ########

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^


clean:
	rm -f *~ *.out
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*
	rm -f $(SRCDIR)/*~
	rm -f $(INCDIR)/*~
