/*
 *  disarm.c
 *  DisARM
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int SignExtend(unsigned int x, int bits);
int Rotate(unsigned int rotatee, int amount);

void DecodeInstruction(unsigned int instr, char *decodeStr)
{
    /* Insert your code here to decode the ARM instruction */
    printf("hello world");
}   

int SignExtend(unsigned int x, int bits)
{
    int r;
    int m = 1U << (bits - 1);
    
    x = x & ((1U << bits) - 1);
    r = (x ^ m) - m;
    return r;
}
               
int Rotate(unsigned int rotatee, int amount)
{
    unsigned int mask, lo, hi;

    mask = (1 << amount) - 1;
    lo = rotatee & mask;
    hi = rotatee >> amount;

    rotatee = (lo << (32 - amount)) | hi;
    
    return rotatee;
}

