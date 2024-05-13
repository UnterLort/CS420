# Makefile for dataDump.c and calSpan.c
CC = gcc
CFLAGS = -Wall -std=c99

all: dataDump.o calSpan.o

dataDump.o: dataDump.c
	$(CC) $(CFLAGS) -c dataDump.c -o dataDump.o

calSpan.o: calSpan.c
	$(CC) $(CFLAGS) -c calSpan.c -o calSpan.o

clean:
	rm dataDump.o calSpan.o