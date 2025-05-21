#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct idStudent
{
    int id;
    char firstName[50];
    char lastName[50];

}idStudent;

typedef struct idScore
{
    int id;
    int score;
}idScore;


void studentList_init(idStudent * idStudentP,char * filename);
void scoreList_init(idScore * idScoreP, char * filename);
void linkStudent2Score(idStudent * idStudentP,idScore * idScoreP,int nStudents, int nScores);

int countLines(char * filename);

int main (int argc, char *argv[]) {

    /*setup the arrays to store the values for the 2 structure lists*/
    idStudent * idStudentsList; /*Each element is a struct not pointer to struct - so treat like class vars from python -- '.'*/
    idScore * idScoreList;

    int Nstudents;
    int Nscores;    


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

    if (strcmp(argv[1],argv[2])==0){
        fprintf(stderr,"cannot enter the same file twice\n");
        return 1;
    }

    if (strstr(argv[1],"students.csv")==NULL){
        fprintf(stderr,"must enter student file first");
        return 1;
    }

    Nstudents = countLines(argv[1]);
    if (Nstudents<=0){
        fprintf(stderr,"Student file is empty\n");
        return 1;
    }

    idStudentsList = malloc(Nstudents*sizeof(idStudent));
    
    Nscores = countLines(argv[2]);
    if (Nscores<0){
        fprintf(stderr,"scores file is empty");
        return 1;
    }

    idScoreList = malloc(Nscores*sizeof(idScore));

    studentList_init(idStudentsList,argv[1]);
    scoreList_init(idScoreList,argv[2]);

    linkStudent2Score(idStudentsList,idScoreList,Nstudents,Nscores);
    
    /*free dynamic memory*/
    free(idStudentsList);
    free(idScoreList);

    return 0;
}

void studentList_init(idStudent * idStudentP,char * filename){
    int count = 0; /*counts the number of newlines so knows where it is at in the file*/
    char line[256];
    FILE * filepointer = fopen(filename,"r");

    fgets(line, sizeof(line), filepointer);  /*skip header line*/
 

    while(fgets(line,sizeof(line),filepointer)){
        sscanf(line, "%d,%49[^,],%49[^\n]", &idStudentP[count].id, idStudentP[count].lastName, idStudentP[count].firstName);       
        count++;
    }
    fclose(filepointer);
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

void scoreList_init(idScore * idScoreP, char * filename){
    int count = 0;
    char line[256];
    FILE * filepointer = fopen(filename,"r");

    fgets(line,sizeof(line),filepointer);

    while (fgets(line,sizeof(line),filepointer)){
        sscanf(line,"%d,%d",&idScoreP[count].id,&idScoreP[count].score);
        count++;
    }
    fclose(filepointer);
}

void linkStudent2Score(idStudent * idStudentP,idScore * idScoreP, int nStudents,int nScores){
    int i; /*look just iterate through until a match is found then break*/
    int j;
    int found; /*0 - false, 1 - true*/

    for (i=0;i<nStudents;i++){
        found = 0;
        for (j=0;j<nScores;j++){
            if (idScoreP[j].id == idStudentP[i].id){
                printf("%s %s %d\n",idStudentP[i].firstName,idStudentP[i].lastName,idScoreP[j].score);
                found = 1;
                break;
            }
        
        }

        if (!found){
            printf("%s %s %d\n",idStudentP[i].firstName,idStudentP[i].lastName,0);
        }
    }
    
}