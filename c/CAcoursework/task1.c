/*elementary cellular automata in ascii art*/

#include <stdio.h>
#include <stdlib.h>

int intToBin(int value,int * ptobin);
int binToInt(int * binNum, int length);
int getBinfromChar(char symbol);
char getCharFromBin(int binNum);

int main (int argc, char *argv[]) {
    char * rowP = (char *) malloc(atoi(argv[0])+1 * sizeof(char)); /* set up the pointer to the array for the current generation*/
    char * rowPNG = (char *) malloc(atoi(argv[0])+1 * sizeof(char)); /* the array set up to be the next generation*/

    int i;
    int j;
    int gen;
    int cell;
    int binToIntVal;
    
    int inputs[3]; /* 0 is No 1d cells, 1 is No generations, 2 is the wolfram code */

    int binval[8]; /* revresed binary string to make translation to ruleset easier*/

    if (argc != 4){
        printf("Must enter 3 paramaters");
        return 1;
    }

    /*Convert the inputs into an integer array*/

    for (i=1;i<argc;i++){
        inputs[i-1] = atoi(argv[i]);
    }


    for (i = 0;i<inputs[0];i++){
        *(rowP+i) = ' ';
    }
   
    *(rowP+inputs[0]/2) = '*';
    /*check the input values are valid*/

    if (inputs[0]<=0 || inputs[1] <=0){
        printf("cannot have Number of cells or generations less than 1");
        return 1;
    }

    if (inputs[2]<0 || inputs[2]>255){
        printf("The wolfram code must be between 0 and 255 inclusive");
        return 1;
    }

    intToBin(inputs[2],binval); /* creates the reversed binary string to be used for the wolfram code*/

    /* */
    for (i = 0;i<inputs[0];i++){
        printf("%c",*(rowP+i));
    }
    printf("\n");
    /* ^^ just for debugging*/



    /* Where the logic actually begins - ^^ Setup ^^*/
    for (gen = 1; gen<inputs[1];gen++){

        for (i = 0; i<inputs[0];i++){
            rowPNG[i] = '/';
        }

        rowPNG[0] = ' ';
        rowPNG[inputs[0]] = ' ';

        for (cell = 1;cell<=inputs[0]-1;cell++){ /* cell from 1 to size - 1 so doesnt over flow /* iterates over every cell*/

            /* right neighbour, itself, left neighbour -- needs to be converted to binary*/
            int shortbin[3];
            shortbin[0] = *(rowP + cell + 1);
            shortbin[1] = *(rowP + cell);
            shortbin[2] = *(rowP + cell - 1);

            

            for (j = 0;j<3;j++){

                shortbin[j] = getBinfromChar(shortbin[j]);
            }
        

            binToIntVal = binToInt(shortbin,sizeof(shortbin)/sizeof(shortbin[0]));

            rowPNG[cell] = getCharFromBin(binval[binToIntVal]); /* fill in the new generation values*/
        }

        /* copy the new cells from the new generation into the old generation so the cycle can be started again*/
        for (i = 0;i<inputs[0];i++){
            rowP[i] = rowPNG[i];
        }

        for (cell = 0;cell<inputs[0];cell++){
            printf("%c",rowP[cell]);
        }
        
        printf("\n");
    }

    free(rowP);
    free(rowPNG);

    return 0;
}

char getCharFromBin(int binNum){
    if (binNum == 1){
        return '*';
        
    }

    return ' '; 
}

int getBinfromChar(char symbol){
    if (symbol == '*'){
        return 1;
    }

    return 0;
}

int intToBin(int value,int * ptobin){
    /*Repeated division by 2 method*/
    int i;
    for (i = 0;i<=7;i++){
        *(ptobin+i) = value&1;
        value = value>>1;
    }

    /*No need to create rule set, can just ref appropriate position in the inttobin array*/

    /*store binary array in reverse to make it easier to call the needed rule based on value*/

    return * ptobin;
}


int binToInt(int * binNum, int length){
    /*assumes the binary string is reversed -> LSB -> MSB not MSB -> LSB*/
    int i;    
    int intNum = 0;
    for (i = 0;i<length;i++){
        if ((*(binNum+i)&1)){
            intNum += 1<<i;
        }
    }

    return intNum;
}