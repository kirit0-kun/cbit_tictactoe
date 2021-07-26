TARGET=tictactoe
CC=gcc
CFLAGS=-g -Wall

LIBS=-lc
INC=-I. -Iheaders

SRCDIR= src
BUILDDIR= build

SRCS=$(SRCDIR)/main.c $(SRCDIR)/bit_utils.c $(SRCDIR)/game.c

OBJS = $(patsubst %, $(BUILDDIR)/%, $(notdir $(SRCS:.c=.o)))

all: buildFiles
	./$(BUILDDIR)/${TARGET}

leaks: buildFiles
	./$(BUILDDIR)/${TARGET}

buildFiles: $(BUILDDIR) $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(CC) $(CFLAGS) $(INC) -S $< -o $(@:.o=.s)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(BUILDDIR)/$@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -f -r *.o $(TARGET) *.s *.h.gch *.dSYM $(BUILDDIR)

clear: clean
	clear