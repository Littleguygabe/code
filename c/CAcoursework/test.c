#include <stdio.h>
#include <stdlib.h>

int * intToBin(int num, int * ptobin, int size);

int main (int argc, char *argv[]) {
    int seed = atoi(argv[1]);

    int size = 16;
    int ptobin[size];
    int i;

    int Ncells = 10;

    intToBin(seed,ptobin,size);

    for (i=0;i<(size);i++){
        printf("%d",*(ptobin+i));
    } 
    return 0;
}

int * intToBin(int num,int * ptobin,int size){

    /*Repeated division by 2 method*/
    int i;

    for (i = 0;i<=size;i++){
        *(ptobin+(size-1-i)) = num&1;
        num = num>>1;
    }

    return ptobin;
}