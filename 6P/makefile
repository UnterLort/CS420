# Kyle Stewart.
# File: makefile
# Project: makefile
# Purpose: Contains build instructions for the project
# 4/17/2024.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Declare phony targets
.PHONY: all clean

# Default target: build the gol executable
all: gol

# Target to build gol executable
gol: gol.o golFunctions.o
	$(CC) $(CFLAGS) -o gol gol.o golFunctions.o

# Target to compile gol.c into gol.o
gol.o: gol.c gol.h
	$(CC) $(CFLAGS) -c gol.c

# Target to compile golFunctions.c into golFunctions.o
golFunctions.o: golFunctions.c gol.h
	$(CC) $(CFLAGS) -c golFunctions.c

# Target to clean up object and executable files
clean:
	rm -f gol gol.o golFunctions.o