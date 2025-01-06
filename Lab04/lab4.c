/**
 * File:    lab.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Oct 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which the user sends a text file through the command line
 *      to convert binary numbers and prints the decimal values of the binary inputs.
 *
 */

#include <stdio.h>
#include <math.h>

/**
 *
 * void binToDecConverter(FILE *fptr)
 *
 * Summary of the Converter function:
 *
 *      The converter function reads from a file parameter for the rows and columns of the
 *      binary numbers for conversion. The function proceeds to convert the numbers based
 *      on the given rows and columns in the first row of the file.
 *
 *  Parameters  : file pointer: points to the data in the file.
 *
 *  Return Value: Nothing -- prints the binary numbers read from the file.
 *
 * */

void binToDecConverter(FILE *fptr){

    int row, column,base, dec, bin = 0;

    if (fscanf(fptr,"%d""%d", &row, &column) != 2)
    {
        printf("Error: wrong inputs in the first row of the file.");
        return;
    }

    base = column - 1;

    for (int i = 0; i < row; ++i) {

        for (int j = 0; j < column; ++j) {
            fscanf(fptr,"%d", &bin);

            if(bin < 0 || bin > 1){
                printf("Error: invalid input on row %d", i + 1);
                return;
            }
            dec = dec + bin * pow(2, base);
            base--;
        }
        printf("%d\n", dec);
        dec = 0;
        base = column - 1;
    }
}

/**
 *
 * int main(int argc, char **argv)
 *
 * Summary of the main function:
 *
 *  The main function runs the program and the functions in the file.
 *
 *Parameters  : char pointer to pointer: points to the data in the file.
 *
 *Return Value: Integer number 1 or 0 that denotes if the program runs without errors.
 *
 *Description:
 *  The main function opens a file in read mode and assigns a pointer to read from it.
 *  The function then calls the binToDecConverter function.
 *
 * */

int main(int argc, char **argv) {
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Error: file does not exist.");
    } else {

        binToDecConverter(fp);
    }


    fclose(fp);
    return 0;
}
