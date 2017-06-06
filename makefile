################################################################################
# NAME: makefile
# AUTHOR: Ethan D. Twardy
# DESCRIPTION: makefile for the executable contained in this directory.
# CREATED: 06/05/17
# LAST EDITED: 06/05/17
################################################################################

P = linkedlist
OBJECTS = linkedlist.c
CFLAGS = -Wall -O3
LDLIBS=
CC=gcc

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LDLIBS)

.PHONY: debug clean

CFLAGS_DEBUG = -g -Wall -D CONFIG_DEBUG

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(P) $(OBJECTS) $(LDLIBS)

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf makefile~