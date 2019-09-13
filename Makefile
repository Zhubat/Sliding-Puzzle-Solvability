#Makefile for Assignment 1
CC=dcc
CFLAGS=-Wall

puzzle: puzzle.o boardADT.o
	$(CC) -o puzzle puzzle.o boardADT.o -lm
puzzle.o: puzzle.c boardADT.h
	$(CC) $(CFLAGS) -c puzzle.c
boardADT.o: boardADT.c boardADT.h
	$(CC) $(CFLAGS) -c boardADT.c
clean:
	rm -f puzzle *.o core
