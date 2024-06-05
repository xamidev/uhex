CC=gcc
CFLAGS=-g -Wall -Wextra -o
CFILES=hex.c

all:
	$(CC) $(CFILES) $(CFLAGS) uhex

install: all
	sudo cp uhex /usr/local/bin

clean:
	rm uhex
