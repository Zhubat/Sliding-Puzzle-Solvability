#include <stdio.h>

#ifndef BOARDADT_H
#define BOARDADT_H


//Function to read input from stdin
int *getinput(FILE *fp);
//Function to check validity of input from stdin
int validInput(int *pointer, int n);
//Check 1...N-1 range
int validRange(int *pointer, int n);
//Function to print pointer
void printResult(int *pointer, int n);
//Function to get size of board, e.g. 16 inputs, sqrt(16) = 4
int checkSize(int n);
/*Function to calculate disorders for parity */
int disorderOdd(int *pointer, int n);
int disorderEven(int *pointer, int n, int b_size);
//Function to compare parity for solvability
void solvability(int a, int b);
#endif
