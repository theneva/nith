SHELL = /bin/sh

.SUFFIXES: .c .o

CC = gcc

CFLAGS = -std=c11 -Wall -Werror

EXECUTABLE = bin/game

# ALL the files to be compiled
FILES = lib/boolean.c game.c player.c item.c room.c

all: $(EXECUTABLE)
$(EXECUTABLE) : $(FILES)
	$(CC) $(FILES) $(CFLAGS) -o $(EXECUTABLE)

clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)
