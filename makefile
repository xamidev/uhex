CC=gcc
CFLAGS=-g -Wall -Wextra -o
CFILES=hex.c

all:
	$(CC) $(CFILES) $(CFLAGS) minihex

clean:
	rm minihex
