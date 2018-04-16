###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Singly-Linked List.
#
# CREATED:	    05/05/2017
#
# LAST EDITED:	    04/16/2018
###

CC=gcc
ifeq ($(MAKECMDGOALS),debug)
	CFLAGS = -g -O0 -Wall -Wextra -pedantic -D CONFIG_DEBUG_LIST
else
	CFLAGS = -Wall -O3
endif

.PHONY: debug clean

list:

debug: list

clean:
	rm -rf *.dSYM
	rm -f *.o
	rm -f list

###############################################################################
