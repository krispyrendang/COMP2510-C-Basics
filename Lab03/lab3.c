#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printReversedTokens(char *inputString, int strLen){

    int chk = strlen(inputString);
    char format[strLen];
    int count = -1;

    //Checks if the correct string length is provided,
    //otherwise, the program will not run.
    if(chk == strLen){

        //iterates through the inputString array
        for(int i = 0; i < strLen; i++){

            //Checks for conditions to print when a space is found
            if (inputString[i] == ' '){

                //Checks if anything is stored in the second array that
                //collects the valid char for printing.
                if(count >= 0){
                    //prints the char stored in format array in reverse
                    for (int j = count; j >= 0; j--) {
                        if(format[j] != '0'){
                            printf("%c", format[j]);
                        }

                        //checks for end of the format array to print a new line
                        //and reset the counter that increments when format array stores new char.
                        if ((j == 0) && format[count] != 0) {
                            printf("\n");
                            count = -1;
                        }
                    }
                }
            } else {
                //No space detected, store char to the format array and increment the counter.
                if(inputString[i] != 0){
                    count++;
                    format[count] = inputString[i];
                }
            }
        }
        //prints the last word that does not end with a space.
        for (int k = count; k >= 0; k--) {
            if (format[k] != 0){
                printf("%c", format[k]);
            }
        }
    } else {
        printf("Please check the input string length again.");
    }
}

int main(int argc, char **argv){
  printReversedTokens(argv[1], atoi(argv[2]));
  return 0;
}
