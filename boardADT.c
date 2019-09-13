#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boardADT.h"

/*Function declerations */
//Function to read input from stdin and return a pointer to a block of memory
int *getinput(FILE *fp){
    char *pointer;  //char pointer
    int *p_int; //int pointer
    //variables
    //c = individual read character
    //rx, ix used for conversion, ix is each int after a ' '
    //m and mm are incrememnters, m of char pointer starts at 2 since
    //block [0] is reserved and block [1] is padded ' ',
    //m starts at 1 since block [0] of int pointer is reserved for size
    int c, rx, ix = 2, m = 2, mm = 1, temp_r = 0;

    //Start with allocating pointer with initial memory
    //Given + 10 to allow adequate room
    pointer = (char*)malloc((m + 10) * sizeof(char));
    *(pointer + 1) = ' ';   //pad ' ' so memory block [0] is seperated
    //Read characters 1 by 1 until end of input or '\n' (ENTER key)
    while ((c = fgetc(fp)) != EOF && c != '\n'){
        //only numbers and 'b' is accepted
        if ((c >= '0' && c <= '9') || c == 'b'){
            *(pointer + m) = c; //Store character to memory under pointer
            m++;    //increment count/size
            //Allocate additional memory ready for the next character
            pointer = realloc(pointer, (m + 10) * sizeof(char)); 

        }
        //Error case when input contains invalid characters, e.g. $, %, #, etc
        else if (c != ' ' && c != '\t' && c != '\v' && c != '\f' && c != '\r'){
            printf("ERROR: input contains incorrect characters/number.\n ");
            exit(EXIT_FAILURE);
        }
        //Format so all blanks > 0 is replaced by 1 x ' ' between each input number
        else{
            //If the last stored character isnt a blank(' ')
            if (*(pointer + (m-1)) != ' '){
                //Add a SINGLE ' ' after every number/character
                *(pointer + m) = ' ';
                m++;
                pointer = realloc(pointer, (m + 10) * sizeof(char));
            }
        }
    }
    //If the last stored item in memory is not a ' ' char
    if (*(pointer + (m - 1)) != ' '){
        //Makes sure the last input of a board ends with ' ' after
        *(pointer + m) = ' ';
        m++;
    }
    //Ready to convert input read from char to int
    //Allocate memory for int pointer with size equal to char pointer memory
    p_int = (int*)malloc(m * sizeof(int));
    //Start from 2 since block[2] is the first number char
    for (int i = 2; i < m; i++){
        //When a ' ' is reached
        if (*(pointer + i) == ' '){
            //If item is char 'b', replace with unique int 0
            if (*(pointer + (i - 1)) == 'b'){
                *(p_int + mm) = 0;
                mm++;
                //The next first number char is after ' '
                ix = i + 1;
            }
            //If more than one number char in a row combine them,
            //e.g. input char '1' + '2' becomes int 12
            else{
                rx = i - ix;
                while (rx != 0){
                    temp_r *= 10;
                    temp_r += (*(pointer + (i - rx)) - '0'); //Convert char to int
                    rx--;
                }
                //Only store when char numbers are combined to single int
                *(p_int + mm) = temp_r;
                temp_r = 0;
                mm++;
                ix = i + 1;
            }
        }
    }
    //Reallocate memory to free excess memory
    p_int = realloc(p_int, mm * sizeof(int));
    *(p_int + 0) = mm;  //store size to block [0]
    free(pointer);  //free char pointer
    //Return int pointer
    return p_int;
}

int validInput(int *pointer, int n){
    int b_in = 0;

    //Checks for if 'b' exists in input
    for (int i = 1; i < n; i++){
        if (*(pointer + i) == 0){
            b_in = 1;   //when 'b' DO exists.
        }
    }
    //If no 'b' in input
    if (b_in != 1){
        return 1;
    }
    else{
        return 2;   //Input is valid
    }
}

int validRange(int *pointer, int n){
    int in_range = 0, range_sum = 0;

    //Check int pointer if all items match range of numbers
    for (int i = 1; i < n - 1; i++){
        for (int ii = 1; ii < n; ii++){
            if (*(pointer + ii) == i){
                in_range = 1;
            }
        }
        range_sum += in_range;
        in_range = 0;
    }
    if (range_sum != (n - 2)){
        return 1;   //Case when missing number from 1...N-1 range
    }
    else{
        return 0;   //Case for valid
    }
}

void printResult(int *pointer, int n){
    for (int i = 1; i < n; i++)
    {
        if (*(pointer + i) == 0){
            printf(" b");
        }
        else{
            printf(" %d", pointer[i]);
        }
    }
    printf("\n");
}

int checkSize(int n){
    double rtemp_a, rtemp_b, t;
    int root;

    t = n - 1;  //n - 1 e.g. if n is 17, (0~16)
    rtemp_a = sqrt(t);  //result in double, e.g. 4.00 or 4.222
    root = (int) rtemp_a;   //root is int, e.g. 4.222 > 4
    rtemp_b = (double) root;    //rtemp_b is e.g. 4 > 4.00
    if (rtemp_a == rtemp_b){
        //If result has no remainders
        return root;
    }
    else{
        //If result contains remainders, therefore not N x N
        return 0;
    }
}

//Odd parity
int disorderOdd(int *pointer, int n){
    int d1, d2, sum = 0, x = 0;

    for (int i = 1; i < n; i++)
    {
        if (*(pointer + i) != 0)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (*(pointer + j) != *(pointer + i) && *(pointer + j) != 0)
                {
                    d1 = *(pointer + i);
                    d2 = *(pointer + j);
                    if (d1 > d2)
                    {
                        x++;
                    }
                }
            }
            sum += x;
            x = 0;
        }
    }
    return sum;
}

//Even parity
int disorderEven(int *pointer, int n, int b_size){
    int d1, d2, blank, blank_square, sum = 0, x = 0;

    for (int i = 1; i < n; i++)
    {
        if (*(pointer + i) != 0)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (*(pointer + j) != *(pointer + i) && *(pointer + j) != 0)
                {
                    d1 = *(pointer + i);
                    d2 = *(pointer + j);
                    if (d1 > d2)
                    {
                        x++;
                    }
                }
            }
            sum += x;
            x = 0;
        }
        else{
            blank = i;
        }
    }
    if (blank % b_size == 0){
        blank_square = blank/b_size;
    }
    else{
        blank_square = blank/b_size + 1;
    }
    sum += blank_square;
    return sum;
}

void solvability(int a, int b){
    if (a % 2 == 0 && b % 2 == 0){
        //Both odd parity
        printf("solvable");
    }
    else if (a % 2 != 0 && b % 2 != 0){
        //Both even parity
        printf("solvable");
    }
    else{
        printf("unsolvable");
    }
}
