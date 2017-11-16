################################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Singly-Linked List.
#
# CREATED:	    05/05/2017
#
# LAST EDITED:	    11/15/2017
###

P = linkedlist
OBJECTS = linkedlist.c
CFLAGS = -Wall -O3
LDLIBS=
CC=gcc

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LDLIBS)

.PHONY: debug clean

CFLAGS_DEBUG = -g -O0 -Wall -D CONFIG_DEBUG_LIST

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(P) $(OBJECTS) $(LDLIBS)

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf makefile~

################################################################################
