TARGET=tictactoe
CC=gcc
CFLAGS=-g -Wall

LIBS=-lc
INC=-I.

SRCS=main.c bit_utils.c game.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
	./${TARGET}

leaks: $(TARGET)
	./${TARGET}
	
%.o: %.c %.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(CC) $(CFLAGS) $(INC) -S $^

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

clean:
	rm -f -r *.o $(TARGET) *.s *.h.gch *.dSYM

clear: clean
	clear