#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    char * p = (char *) calloc(10,sizeof(char));

    for (int i = 0;i<10;i++){
        *(p+i) = 'G';
        printf("%s",*(p+i));
    }
    
 
    return 0;
}