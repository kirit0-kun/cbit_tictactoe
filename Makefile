TARGET=tictactoe
CC=gcc
CFLAGS=-g -Wall

BASE_LIBS_LOC=.
BASE_LIBS=c
BASE_INC=. headers
SRCDIR= src
BUILDDIR= build
BASE_SRCS=main.c bit_utils.c game.c

INC=$(patsubst %, -I%, $(BASE_INC))
LIBS_LOC=$(patsubst %, -L%, $(BASE_LIBS_LOC))
LIBS=$(patsubst %, -l%, $(BASE_LIBS))
SRCS=$(patsubst %, $(SRCDIR)/%, $(BASE_SRCS))
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
	$(CC) $(CFLAGS) $(LIBS_LOC) $(LIBS) -o $(BUILDDIR)/$@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -f -r *.o $(TARGET) *.s *.h.gch *.dSYM $(BUILDDIR)

clear: clean
	clear