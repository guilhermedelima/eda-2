INCDIR=include
BINDIR=bin
OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-W -Wall -I $(INCDIR)

TARGET=greedy_task

_HEADER=greedy_task.h
_OBJ=greedy_task.o merge_sort.o test_greedy_task.o

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
