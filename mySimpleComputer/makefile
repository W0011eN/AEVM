DIR=build bin
OBJECTS=build/main.o build/memory.o build/terminal.o
CC=gcc
CFLAGS=-c -Wall -std=c99
#//////////////////////////////////////////////////////
.PHONY: all clean makedir

#//////////////////////////////////////////////////////
all:  makedir main memory terminal test_mSC

makedir:
	mkdir -p $(DIR) 
main:src/main.c
	$(CC)  -o build/main.o $(CFLAGS) -Werror src/main.c 

memory:src/memory.c
	$(CC)  -o build/memory.o $(CFLAGS)   -Werror src/memory.c

terminal:src/terminal.c
	$(CC)  -o build/terminal.o $(CFLAGS)   -Werror src/terminal.c

test_mSC: $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/mSC


clean:
	rm -rf build/*.* bin/* bin/*.*
