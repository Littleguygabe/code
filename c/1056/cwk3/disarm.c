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

unsigned int getHexval(int nobits){
    return (1U<<nobits)-1;
}

unsigned int getBitValues(unsigned int binstring, int startBit, int endBit){
    int noBits = (endBit - startBit + 1);
    unsigned int hexVal = getHexval(noBits);
    unsigned int mas = hexVal << startBit;
    unsigned int result = (binstring&mas)>>startBit;

    return result;
    
}

void setupSWI(char ** instructionLine,unsigned int instruction){
    unsigned int SWIval = getBitValues(instruction,0,23);

    instructionLine[5] = malloc(20*sizeof(char));

    if (SWIval>9){
        sprintf(instructionLine[5]," 0x%X",SWIval);
    }
    else{
        sprintf(instructionLine[5]," %X",SWIval);
    }


}

void handleBranch(char**instructionLine, unsigned int instruction){
    char * suffix;
    unsigned int condCode = getBitValues(instruction,28,31);
    unsigned int branchVal;

    instructionLine[5]= malloc(20*sizeof(unsigned int)); 

    /*see if is branch and exchange*/


    switch (condCode) {
        case 0:  suffix = "EQ"; break;
        case 1:  suffix = "NE"; break;
        case 2:  suffix = "CS"; break;
        case 3:  suffix = "CC"; break;
        case 4:  suffix = "MI"; break;
        case 5:  suffix = "PL"; break;
        case 6:  suffix = "VS"; break;
        case 7:  suffix = "VC"; break;
        case 8:  suffix = "HI"; break;
        case 9:  suffix = "LS"; break;
        case 10: suffix = "GE"; break;
        case 11: suffix = "LT"; break;
        case 12: suffix = "GT"; break;
        case 13: suffix = "LE"; break;
        case 14:
            if (getBitValues(instruction,24,24)==1){
                suffix = "L";
            }
            else{
                suffix="";
            }
            break; /*for when branch always*/
    
        default: suffix=""; break;
    }

    sprintf(instructionLine[3],"B%s",suffix);

    /*then just put that value of the branch instruction into the opcode value holder --> instruction line 5*/

    branchVal = getBitValues(instruction,0,23);
    sprintf(instructionLine[5]," %d",SignExtend(branchVal,24)*4);

}

void handleDataprocessing(char **instructionLine, unsigned int instruction) {
    unsigned int opcode = getBitValues(instruction, 21, 24);
    unsigned int rn = getBitValues(instruction, 16, 19);
    unsigned int rd = getBitValues(instruction, 12, 15);
    unsigned int operand2 = getBitValues(instruction, 0, 11);
    unsigned int iBit = getBitValues(instruction, 25, 25);

    unsigned int imm,rotate,rotatedImm,rm,shiftType,shiftAmount;

    char * shiftMnemonic;

    instructionLine[3] = (char *)malloc(10 * sizeof(char));
    instructionLine[5] = (char *)malloc(20 * sizeof(char));
    instructionLine[6] = (char *)malloc(20 * sizeof(char));

    if (instructionLine[3] == NULL || instructionLine[5] == NULL || instructionLine[6] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    switch (opcode) {
        case 0: sprintf(instructionLine[3], "AND"); break;
        case 1: sprintf(instructionLine[3], "EOR"); break;
        case 2: sprintf(instructionLine[3], "SUB"); break;
        case 3: sprintf(instructionLine[3], "RSB"); break;
        case 4: sprintf(instructionLine[3], "ADD"); break;
        case 5: sprintf(instructionLine[3], "ADC"); break;
        case 6: sprintf(instructionLine[3], "SBC"); break;
        case 7: sprintf(instructionLine[3], "RSC"); break;
        case 8: sprintf(instructionLine[3], "TST"); break;
        case 9: sprintf(instructionLine[3], "TEQ"); break;
        case 10: sprintf(instructionLine[3], "CMP"); break;
        case 11: sprintf(instructionLine[3], "CMN"); break;
        case 12: sprintf(instructionLine[3], "ORR"); break;
        case 13: sprintf(instructionLine[3], "MOV"); break;
        case 14: sprintf(instructionLine[3], "BIC"); break;
        case 15: sprintf(instructionLine[3], "MVN"); break;
        default: sprintf(instructionLine[3], "UNK"); break;
    }

    if (opcode >= 8 && opcode <= 11) {
        sprintf(instructionLine[5], " R%d", rn);
        sprintf(instructionLine[6], " Operand2");
    } else if (opcode == 13 || opcode == 15) {
        sprintf(instructionLine[5], " R%d", rd);
        sprintf(instructionLine[6], " Operand2");
    } else {
        sprintf(instructionLine[5], " R%d,R%d", rd, rn);
        sprintf(instructionLine[6], " Operand2");
    }

    if (iBit == 1) {
        imm = getBitValues(operand2, 0, 7);
        rotate = getBitValues(operand2, 8, 11);
        rotatedImm = Rotate(imm, rotate * 2);
        sprintf(instructionLine[6], " #%d", rotatedImm);
    } else {
        
        rm = getBitValues(operand2, 0, 3);
        shiftType = getBitValues(operand2, 5, 6);
        shiftAmount = getBitValues(operand2, 7, 11);
        switch (shiftType) {
            case 0: shiftMnemonic = "LSL"; break;
            case 1: shiftMnemonic = "LSR"; break;
            case 2: shiftMnemonic = "ASR"; break;
            case 3: shiftMnemonic = "ROR"; break;
            default: shiftMnemonic = ""; break;
        }
        if (shiftAmount > 0) {
            sprintf(instructionLine[6], ",R%d %s #%d", rm, shiftMnemonic, shiftAmount);
        } else {
            sprintf(instructionLine[6], ",R%d", rm);
        }
    }

}




void handleLDRSTR(char **instructionLine, unsigned int instruction) {
    unsigned int iBit, pBit, uBit, wBit, lBit, rn, rd, offset, rm, shiftType, shiftAmount;
    int signedOffset;
    char *shiftMnemonic;
    iBit = getBitValues(instruction, 25, 25);
    pBit = getBitValues(instruction, 24, 24);
    uBit = getBitValues(instruction, 23, 23);
    wBit = getBitValues(instruction, 21, 21);
    lBit = getBitValues(instruction, 20, 20);

    instructionLine[3] = malloc(10 * sizeof(char));
    instructionLine[5] = malloc(20 * sizeof(char));
    instructionLine[6] = malloc(40 * sizeof(char));

    if (instructionLine[3] == NULL || instructionLine[5] == NULL || instructionLine[6] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    if (getBitValues(instruction,22,22)==0){
        sprintf(instructionLine[3], "%s", lBit ? "LDR" : "STR");
    }

    else{
         sprintf(instructionLine[3], "%s", lBit ? "LDRB" : "STRB");        
    }

    rn = getBitValues(instruction, 16, 19);
    rd = getBitValues(instruction, 12, 15);

    if (iBit == 0) {
        offset = getBitValues(instruction, 0, 11);
        signedOffset = uBit ? offset : -offset;

        if (pBit == 1 && wBit == 0) {
            if (signedOffset!=0){
                sprintf(instructionLine[5], " R%d,[R%d, #%d]", rd, rn, signedOffset);
            }
            else{
                sprintf(instructionLine[5], " R%d,[R%d]", rd, rn);   
            }
        } else if (pBit == 1 && wBit == 1) {
            sprintf(instructionLine[5], " R%d,[R%d, #%d]!", rd, rn, signedOffset);
        } else if (pBit == 0) {
            sprintf(instructionLine[5], " R%d,[R%d], #%d", rd, rn, signedOffset);
        }
    } else {
        rm = getBitValues(instruction, 0, 3);
        shiftType = getBitValues(instruction, 5, 6);
        shiftAmount = getBitValues(instruction, 7, 11);

        switch (shiftType) {
            case 0: shiftMnemonic = "LSL"; break;
            case 1: shiftMnemonic = "LSR"; break;
            case 2: shiftMnemonic = "ASR"; break;
            case 3: shiftMnemonic = "ROR"; break;
            default: shiftMnemonic = ""; break;
        }

        if (pBit == 1 && wBit == 0) {
            if (shiftAmount > 0) {
                sprintf(instructionLine[5], " R%d,[R%d, R%d %s #%d]", rd, rn, rm, shiftMnemonic, shiftAmount);
            } else {
                sprintf(instructionLine[5], " R%d,[R%d, R%d]", rd, rn, rm);
            }
        } else if (pBit == 1 && wBit == 1) {
            if (shiftAmount > 0) {
                sprintf(instructionLine[5], " R%d,[R%d, R%d %s #%d]!", rd, rn, rm, shiftMnemonic, shiftAmount);
            } else {
                sprintf(instructionLine[5], " R%d,[R%d, R%d]!", rd, rn, rm);
            }
        } else if (pBit == 0) {
            if (shiftAmount > 0) {
                sprintf(instructionLine[5], " R%d,[R%d], R%d %s #%d", rd, rn, rm, shiftMnemonic, shiftAmount);
            } else {
                sprintf(instructionLine[5], " R%d,[R%d], R%d", rd, rn, rm);
            }
        }
    }
}

void handleMLAMUL(char **instructionLine,unsigned int instruction){
    unsigned int rd,rn,rs,rm;
    rd = getBitValues(instruction,16,19);
    rn = getBitValues(instruction,12,15);
    rs = getBitValues(instruction,8,11);
    rm = getBitValues(instruction,0,3);
    instructionLine[5] = malloc(20*sizeof(unsigned int));

    if (getBitValues(instruction,21,21)==0){
            sprintf(instructionLine[5]," R%d, R%d, R%d",rd,rm,rs);
        }
        else{
            sprintf(instructionLine[5]," R%d, R%d, R%d, R%d",rd,rm,rs,rn);
        }
}

void mapToOpcode(char **instructionLine, unsigned int instruction) {
    unsigned int decsisionVal = getBitValues(instruction,25,27); 
    instructionLine[3] = malloc(20 * sizeof(char));

    if (instructionLine[3] == NULL) {
        fprintf(stderr, "Memory allocation failed for instructionLine[3]\n");
        exit(1);
    }

    else if (((instruction >> 24) & 0xF) == 0xF) {
        sprintf(instructionLine[3], "SWI");
        setupSWI(instructionLine, instruction);
        return;
    }


    /*handle mul and mla*/
    if (getBitValues(instruction,22,27)==0&&getBitValues(instruction,4,7)==9){
        if (getBitValues(instruction,21,21)==0){
            sprintf(instructionLine[3],"MUL");
        }
        else{
            sprintf(instructionLine[3],"MLA");
        }

        handleMLAMUL(instructionLine,instruction);
    }

    /*data processing*/
    else if (decsisionVal == 0||decsisionVal==1){
        handleDataprocessing(instructionLine,instruction);
    }



    if (decsisionVal==2||decsisionVal==3){
        handleLDRSTR(instructionLine,instruction);
    }

    /*handling the branching side of things*/
    else if (decsisionVal==5){
        handleBranch(instructionLine,instruction);
    }
    
    else if (getBitValues(instruction,4,27)==0x12FFF1){
        sprintf(instructionLine[3],"BX");
        instructionLine[5] = malloc(20*sizeof(unsigned int));

        sprintf(instructionLine[5]," %d",getBitValues(instruction,0,3));     
    }


}


void DecodeInstruction(unsigned int instr, char *decodeStr)
{
    /* Insert your code here to decode the ARM instruction */
    int i;
    char * instruction[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

    mapToOpcode(instruction,instr);


    for (i=0;i<8;i++){
        if (instruction[i]!=NULL){
            strcat(decodeStr,instruction[i]);
        }
    }

    free(instruction[3]);
    free(instruction[5]);
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

               
        
