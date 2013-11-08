SHELL = /bin/sh

.SUFFIXES: .c .o

CC = gcc

CFLAGS = -std=c11 -Wall -Werror -DIS_DEBUG

EXECUTABLE = client

# ALL the files to be compiled
FILES = client.c binary_search_tree.c linked_int_list.c

all: $(EXECUTABLE)
$(EXECUTABLE) : $(FILES)
	$(CC) $(FILES) $(CFLAGS) -o $(EXECUTABLE)

clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)
