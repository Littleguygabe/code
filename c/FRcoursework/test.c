#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int id;
    int Nscores = 1;
 
    char * splitString;
    char * retrievedLine;

    char line[256];    
    FILE * filepointer = fopen(argv[1],"r");


    int col = 0;
    
    fgets(line,sizeof(line),filepointer);

    while ((fgetc(filepointer))!=EOF){
        col = 1;
        splitString=strtok(fgets(line,sizeof(line),filepointer),","); /*gets the first word of the line*/

        while ((splitString = strtok(NULL,","))!=NULL){
            if (col>=4){
                printf("%s",splitString);
            }
            col++;
        }
    }

    return 0;
}