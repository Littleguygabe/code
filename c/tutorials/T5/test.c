#include <stdio.h>
int binToInt(int * binNum, int length);
int main (int argc, char *argv[]) {

    int arr[3] = {1,1,1};

    printf("%d%d%d in decimal is %d",arr[0],arr[1],arr[2],binToInt(arr,3));

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