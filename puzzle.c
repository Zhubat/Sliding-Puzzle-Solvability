//
// COMP9024 Assignment 1 - Solvability of the NxN sliding tile puzzle
//
// program that determines wether a given puzzle is solvable.
// (Program does not actually solve the puzzle.)
//
// Author: Fan Zhu (z5245075@ad.unsw.edu.au)
//
// Written: 13/06/2019
//
// Program Description:
// The program reads two inputs from stdin of a given format, 
// with first board as start and second board as end goal. 
// The inputs are allocated to memory spaces with designated pointers to them. 
// The inputs are converted to int and reformatted for calculation. 
// The program finds the disorders for the board inputs depending on if board is even or odd.
// Various error checks are in place for the inputs.
//
// The client puzzle.c calls functions in boardADT.c to read input, 
// analyse the boards and calculate their disorders to solve for solvability.
//
// Submission contains:
// puzzle.c
// boardADT.c
// boardADT.h
// a Makefile
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boardADT.h"


int main()
{
    /*Variable declerations */
    /*pointers to memories */
    int *pt_i, *pt_g;              //initial pointers for getting input
    
    /*int variables */
    int boardSize;     //board sizes in 'N x N'
    int disorder_a, disorder_b;     //calculated disorder values
    int b_a, b_b;   //input size
    int valid_a, valid_b;
    int valid_range_1, valid_range_2;

    /*Program begins */
    pt_i = getinput(stdin);          //input 1
    b_a = *(pt_i + 0);                         //size of input 1
    //len_a = checkLength(pt_i, b_a);  //length of input(number of Ns)
    valid_a = validInput(pt_i, b_a); //check validity
    
    pt_g = getinput(stdin);          //input 2
    b_b = *(pt_g + 0);                         //size of input 2
    //len_b = checkLength(pt_g, b_b);  //length of input
    valid_b = validInput(pt_g, b_b); //check validity
    /*Only continue when input contain valid numbers/characters 
    when error is detected, display error messages starting with
     'ERROR: ' printed to stdout */
    if (b_a != b_b){
        printf("ERROR: input are different lengths.\n");
        return EXIT_FAILURE;
    }
    else{
        if (valid_a == 1 || valid_b == 1){
            //Case when input missing character 'b'
            printf("ERROR: an input is missing 'b'.\n");
            return EXIT_FAILURE;
        }
        else{
            boardSize = checkSize(b_a);  //Get board size N of (N x N) sizing
            //Check if board contains 1...N-1 numbers
            valid_range_1 = validRange(pt_i, b_a); 
            /*Continue if board is equal or larger than 2 x 2 and in N x N format */
            if (boardSize >= 2)
            {
                if (boardSize % 2 == 0)
                {
                    //Even parity
                    disorder_a = disorderEven(pt_i, b_a, boardSize);
                }
                else
                {
                    //Odd parity
                    disorder_a = disorderOdd(pt_i, b_a);
                }
                
                /*Input 2 (board 2) analysis */
                valid_range_2 = validRange(pt_g, b_b);
                if (boardSize % 2 == 0)
                {
                    //Even parity
                    disorder_b = disorderEven(pt_g, b_b, boardSize);
                }
                else
                {
                    //Odd parity
                    disorder_b = disorderOdd(pt_g, b_b);
                }

                /*Print/analyse solvability of results if all numbers in range 
                1...N-1 exist in board */
                if (valid_range_1 == valid_range_2 && valid_range_1 == 0)
                {
                    /*Print results to stdout in required format */
                    printf("start:");
                    printResult(pt_i, b_a);
                    printf("goal:");
                    printResult(pt_g, b_b);
                    solvability(disorder_a, disorder_b);
                    printf("\n");
                }
                else
                {
                    //Case missing tile numbers from 1...N-1 range
                    printf("ERROR: input missing tile numbers in 1...N-1 range.\n");
                    return EXIT_FAILURE;
                }
            }
            else
            {
                //Case board is smaller than 2 x 2 or not N x N
                printf("ERROR: board is smaller than 2 x 2 or not in N x N format.\n");
                return EXIT_FAILURE;
            }
        }
    }

    /*Free pointers used for cleanliness */
    free(pt_i);
    free(pt_g);

    /*End of program */
    return EXIT_SUCCESS;
}
