/**
 * File:    lab.c
 *
 * Author:  Taswinder Singh Dhaliwal
 * Date:    Oct 2022
 * Partner: Alan Fung
 * Course:  Comp 2510 - Procedural Programming
 *
 * Summary of file:
 *
 *      This file contains code which the user sends a text file through the command line
 *      to print a string of text that is formatted to justified.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Do NOT change this function's signature including spaces
void formatAndPrintParagraph(FILE *fptr, int lineLength){
  char c = fgetc(fptr);
  int wordnum = 1;
  int maxwordlen = 0;
  int wordlen = 0;


  while (c != EOF) {
    if (c == ' ') {
      wordnum++;
      if (maxwordlen <  wordlen) {
        maxwordlen = wordlen;
      }
      wordlen = 0;
    }
    wordlen++;
    c = fgetc(fptr);
  }

  wordnum *= 2;

  rewind(fptr);
  c = fgetc(fptr);
  char **words;

  words = (char **) malloc(wordnum * maxwordlen * sizeof(char));
  for (int i = 0; i <=  wordnum; i++) {
    words[i] = (char *)malloc(maxwordlen * sizeof(char));
  }
  int chars = 0;
  int index = 0;
  while (c != EOF) {
    if (c == ' ') {
      chars = 0;
      words[index + 1][0] = ' ';
      index += 2;
    } else {
      words[index][chars] = c;
      chars++;
    }
    c = fgetc(fptr);
  }
  int numofchars = 0;
  int numofwords = 0;
  int linestart = 0;
  int *wordsperline;
  wordsperline = (int *) malloc(wordnum/lineLength * sizeof(int));
  int *spacesperline;
  spacesperline = (int *) malloc(wordnum/lineLength * sizeof(int));
  int linecount = 0;
  int charsinline = 0;
  int wordsinline = 0;
  for (int i = 0; i <= wordnum; i++) {
    numofchars = numofchars + strlen(words[i]);
    if (numofchars >= lineLength) {
      numofwords = i;
      numofchars = 0;
      for (int j = linestart; j < numofwords; j++) {
        numofchars = numofchars + strlen(words[j]);
      }
      while (numofchars > lineLength) {
        numofchars = 0;
        for (int j = linestart; j < numofwords; j++) {
          numofchars = numofchars + strlen(words[j]);
        }
        numofwords--;
      }
      charsinline = 0;
      for (int j = linestart; j < numofwords; j++) {
        charsinline = charsinline + strlen(words[j]);
        wordsinline++;
        printf("%s", words[j]);
      }

      printf("\n");
      spacesperline[linecount] = lineLength - charsinline;
      wordsperline[linecount] = wordsinline;
      linecount++;
      numofchars = 0;
      wordsinline = 0;
      linestart = numofwords;
      charsinline = 0;
    }
  }
  for (int j = linestart; j < wordnum; j++) {
    charsinline = charsinline + strlen(words[j]);
    wordsinline++;
    printf("%s", words[j]);
  }

  spacesperline[linecount] = lineLength - charsinline;
  wordsperline[linecount] = wordsinline;

}

// Do NOT touch main function no matter what
int main(int argc, char **argv){
  FILE *fp;

  fp = fopen(argv[1], "r");

  formatAndPrintParagraph(fp, atoi(argv[2]));

  fclose(fp);
  return 0;
}
