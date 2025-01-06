/**
 * File:    reverse.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Oct 2022
 * Partner: I worked alone
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which is called from the main function
 *      in lab5.c and used to reverse the contents of the input file.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "reverse.h"

/**
 *
 * reverseStringOrder(FILE *fptr, int size, int end)
 *
 * Summary of the reverseStringOrder function:
 *
 *      The function reads the file and using recursion it reverses the order
 *      of printing the words.
 *
 *  Parameters  :
 *      file pointer: points to the data in the file.
 *      integer size: the index position from the start of the file that
 *      file pointer is pointing at.
 *      integer end: the length of each word that is required to be reversed.
 *
 *  Return Value: Nothing -- prints the word read from the file.
 *
 * */

void reverseStringOrder(FILE *fptr, int size, int end){

    fseek(fptr, size, SEEK_SET);
    char c = fgetc(fptr);
    if (end > 0){
        reverseStringOrder(fptr, size - 1, end - 1);
        printf("%c", c);
    }
}

/**
 *
 * reverseLineOrder(FILE *fptr, int wordStart, int size, int wordEnd)
 *
 * Summary of the reverseLineOrder function:
 *
 *      The function reads the file and using recursion it reverses the order
 *      of printing the texts lines and insert the spaces appropriately.
 *
 *  Parameters  :
 *      file pointer: points to the data in the file.
 *      integer wordStart: counts the index of each word read from the file.
 *      integer size: the index position from the start of the file that
 *      file pointer is pointing at.
 *      integer wordEnd: stores the length of each word that is required to be reversed.
 *
 *  Return Value: Nothing -- reverses and prints the lines of text read from the file.
 *
 * */

void reverseLineOrder(FILE *fptr, int wordStart, int size, int wordEnd){
    char c = fgetc(fptr);
    if (c != EOF) {

        if (c == '\n' || c == ' '){
            wordEnd = wordStart;
            wordStart = 0;
        } else {
            wordEnd = 0;
            wordStart++;
        }
        fseek(fptr, size, SEEK_SET);
        reverseLineOrder(fptr, wordStart, size + 1, wordEnd);
        if (c == ' ' || c == '\n'){
            reverseStringOrder(fptr, size - 2, wordEnd);
            fseek(fptr, (size - wordEnd - 2), SEEK_SET);
            c = fgetc(fptr);

            if (c == ' '){
                printf(" ");
            } else if (c == '\n'){
                printf("\n");
            }
        }
    }
}

