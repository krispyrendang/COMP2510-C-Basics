#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *fr;
    FILE *fw;
    int result;
    if(argc != 4){
        printf("Error: wrong number of input parameters.");
        return -1;
    }else {
        fr = fopen(argv[1], "r");
        fw = fopen(argv[2], "w");
        int opt = atoi(argv[3]);
        if (fr == NULL || fw == NULL) {
            printf("Error: file does not exist.");
        } else {
            switch (opt) {
                case 1:
                    result = fileParser(fr, fw, 1);
                    break;
                case 2:
                    result = fileParser(fr, fw, 2);
                    break;
                case 3:
                    result = fileParser(fr, fw, 3);
                    break;
                case 4:
                    result = fileParser(fr, fw, 4);
                    break;
                case 5:
                    result = fileParser(fr, fw, 5);
                    break;
                case 6:
                    result = fileParser(fr, fw, 6);
                    break;
                default:
                    printf("Error: invalid option selected.");
                    return -1;
            }
        }

        fclose(fr);
        fclose(fw);

    }


    return 0;
}
