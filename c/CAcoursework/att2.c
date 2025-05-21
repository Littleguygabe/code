#include <stdio.h>
#include <stdlib.h>

/*extras*/
#include <windows.h>
/**/

int getState(int cl,int cc, int cr);
int charToBin(char c);
int binToInt(int * binNum, int length);
char binToCahr(int binNum);

/*extras*/
void clrscr();
int * intToBin(int num, int * ptobin, int size);
/**/

int main (int argc, char *argv[]) {

    int inputs[3]; /*User input values --> 0 is No 1d cells, 1 is No gens, 2 is wolfram code, 3 is the seed in decimal*/
    int TDbinVal[3];

    int row;
    int col;

    int i;
    char * curGen = (char *) calloc(atoi(argv[1]),sizeof(char));
    char * nextGen = (char *) calloc(atoi(argv[1]),sizeof(char)); /*allocate the memory for the generations & setup pointers to mem*/ 

    /*extras -- getting seed from user*/
    int size = 16;
    int ptobin[size];
    
    int seed = atoi(argv[4]);


    if (argc!=4 && argc!=5){
        printf("Must enter atleast 3 parameters");
        return 1;
    }

    /*Convert inputs to integer array*/
    for (i=1;i<argc;i++){
        inputs[i-1] = atoi(argv[i]);
    }

        if (inputs[0]<=0 || inputs[1] <=0){
        printf("cannot have Number of cells or generations less than 1");
        return 1;
    }

    if (inputs[2]<0 || inputs[2]>255){
        printf("The wolfram code must be between 0 and 255 inclusive");
        return 1;
    }

    /*setup the first generation array*/

    if (argc==4){
        for (i=0;i<inputs[0];i++){
            curGen[i] = ' ';
        }
        curGen[inputs[0]/2] = '*';
    }

    else{

        intToBin(seed,ptobin,size);
        if (inputs[0]<size){
            for (i=0;i<inputs[0];i++){
                curGen[i] = binToCahr(*(ptobin+i+(size-inputs[0])));
            }
        }

        else{
            for (i=0;i<inputs[0];i++){
                curGen[i] = ' ';
            }

            for (i=0;i<size;i++){
                curGen[i+((inputs[0]-size)/2)] = binToCahr(*(ptobin+i));
            }
            
        }
    }

    for (i=0;i<inputs[0];i++){
        printf("%d",charToBin(curGen[i]));
    }
    printf("\n");
    
    for (row = 0;row<inputs[1];row++){

        for (i=0;i<inputs[0];i++){
            printf("%c",curGen[i]);
        }

        printf("\n");

        for (col = 0;col<inputs[0];col++){
            /*set up the 3 bit binary value*/
            
            /*set up the wrap around*/
            if ((col-1)<0){
                TDbinVal[0] = charToBin(curGen[col-1+inputs[0]]);  
            }

            else{
                TDbinVal[0] = charToBin(curGen[col-1]);
            }

            TDbinVal[1] = charToBin(curGen[col]);

            if ((col+1)>=inputs[0]){
                TDbinVal[2] = charToBin(curGen[col+1-inputs[0]]);
            }

            else{
                TDbinVal[2] = charToBin(curGen[col+1]);   
            }

            /*Get the value needed for the new cell using the rule provided on moodle*/

            nextGen[col] = binToCahr((inputs[2]>>binToInt(TDbinVal,3))&1);

            
        }
        clrscr();
        for (i=0;i<inputs[0];i++){
                curGen[i]=nextGen[i];
            }
    }

    free(curGen);
    free(nextGen);

    return 0;
}

int getState(int cl,int cc, int cr){
    return 0;
}

int charToBin(char c){
    if (c=='*'){
        return 1;
    }

    return 0;
}

int binToInt(int * binNum, int length){
    int i;    
    int intNum = 0;
    for (i = 0;i<length;i++){
        if ((*(binNum+(length-1-i))&1)){
            intNum += 1<<i;
        }
    }

    return intNum;

}
char binToCahr(int binNum){
    if (binNum){
        return '*';
    }

    return ' ';
}

/*extras*/
void clrscr(){
    Sleep(75);
    system("@cls||clear");
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