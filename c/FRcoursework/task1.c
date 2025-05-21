#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int countLines(char * filename);
void gradeAvg(char * filename, int Nstudents, double * values,int Ngrades);

int max(int num1, int num2);

int main (int argc, char *argv[]) {
    
    int nstudents;
    int ngrades;
    double values[2]; /*[0] is the mean, [1] is the standard deviation*/

    if (argc!=3){
        fprintf(stderr,"Incorrect number of arguments\n");
        return 1;
    }

    if (access(argv[1],R_OK)){
        fprintf(stderr,"File cannot be read\n");
        return 1;
    }
    if (access(argv[2],R_OK)){
        fprintf(stderr,"File cannot be read\n");
        return 1;
    }

    nstudents = countLines(argv[1]);
    ngrades = countLines(argv[2]);


    if (nstudents == -1 || ngrades == -1){
        return 1;
    }

    gradeAvg(argv[2],nstudents,values,ngrades);

    printf("total students = %d\n",nstudents);
    printf("absent students = %d\n",max(0,nstudents-ngrades));
    printf("grade mean = %.2f\n",values[0]);
    printf("grade sd = %.2f\n",values[1]); 
    

    return 0;
}

int countLines(char * filename){
    int Nlines = 0;
    int ch = 0;

    FILE *filePointer = fopen(filename,"r");

    if (!filePointer){
        fprintf (stderr , "error opening %s\n", filename);
        return -1;
    }

    else{
        while(!feof(filePointer)){
            ch = fgetc(filePointer);
            if (ch == '\n'){
                Nlines++;
            } 
        }        
    }
    
    fclose(filePointer);
    return Nlines-1; /*-1 as line 1 is describing the format the data is stored in*/
}

void gradeAvg(char * filename, int Nstudents, double * values,int Ngrades){
    char ch;
    int i;
    float variance = 0;
    float tempVal;
    int count = 0;

    /*int scores[Ngrades];*/

    int * scores = malloc(Ngrades*sizeof(int));


    FILE *filepointer = fopen(filename,"r");
    int total = 0;
    char str[3] = {' ',' ',' '};

 

    while ((ch=getc(filepointer))!=EOF){
        if (ch=='\n'){
            break;
        }
    }

    while ((ch = fgetc(filepointer))!= EOF){
        if (ch == ','){     
            str[0] = fgetc(filepointer);
            str[1] = fgetc(filepointer);
            str[2] = fgetc(filepointer);
            total+=atoi(str);

            scores[count] = atoi(str);
            count++;
        }

    }

    values[0] = total/ (float) Nstudents;

    for (i=0;i<Ngrades;i++){
        tempVal = ((float) scores[i])-values[0];
        variance = variance+(tempVal*tempVal);
    }

    for (i=0;i<(Nstudents-Ngrades);i++){
        tempVal = ((float) 0)-values[0];
        variance = variance+(tempVal*tempVal);
    }

    

    variance = variance/(Nstudents);
    values[1] = sqrt(variance);

    fclose(filepointer);
    free(scores);
}

int max(int num1, int num2){
    if (num1>num2){
        return num1;
    }

    return num2;
}

