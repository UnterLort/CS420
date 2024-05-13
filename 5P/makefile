# Kyle Stewart.
# File: makefile
# Project: makefile
# Purpose: Contains build instructions for the project
# 4/5/2024.

CC = gcc
CFLAGS = -Wall -std=c99

# Target: bitFunctions.o
bitFunctions.o: bitFunctions.c bitFunctions.h
	$(CC) $(CFLAGS) -c bitFunctions.c

# Target: bitTest.o
bitTest.o: bitTest.c bitFunctions.h
	$(CC) $(CFLAGS) -c bitTest.c

# Target: bitTest
bitTest: bitTest.o bitFunctions.o
	$(CC) $(CFLAGS) -o bitTest bitTest.o bitFunctions.o

# Target: ipAddress.o
ipAddress.o: ipAddress.c ipAddress.h
	$(CC) $(CFLAGS) -c ipAddress.c

# Target: clean
clean:
	rm -f bitTest bitTest.o bitFunctions.o ipAddress.o