/**
 * File:    lab5.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Oct 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which the user sends a text file through the command line
 *      to reverse the order of text using recursion and prints to the console.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "reverse.h"

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
 *  The function then calls the reverseLineOrder function in the reverse.c file.
 *
 * */

int main(int argc, char **argv){
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Error: file does not exist.");
    } else {
        reverseLineOrder(fp, 0, 1, 0);
    }
    fclose(fp);

  return 0;
}
