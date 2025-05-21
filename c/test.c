#include <stdio.h>

int main() {

    int i,j = 10;
    int l;

    for (l=0;l<10;l++){
        printf("%d %d",--i,j--);
    }

    return 0;
}
