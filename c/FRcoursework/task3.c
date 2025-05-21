#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct FullStudentData{
    int id;
    char firstName[50];
    char lastName[50];
    float avgScore;
    float * scores;
}FullStudentData;

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

int countLines(char * filename);
void readResults(char * resultsFileName,char * activityFileNam,char * newResultsFilee);
void comStuResults(char * studentsFileName,char * activityFileName,char * newResultsFile);
int countCommas(char * filename);

void studentList_init(idStudent * idStudentP,char * filename);
void scoreList_init(idScore * idScoreP, char * filename);
void linkStudent2Score(idStudent * idStudentP,idScore * idScoreP,int nStudents, int nScores,FullStudentData * studentDataList);
void writeToFile(char * filename,FullStudentData * studentDataList, int nStudents, int nScores);


int main (int argc, char *argv[]) {



    if (argc!=4){
        fprintf(stderr,"Incorrect number of arguments");
        return 1;
    }
    if (access(argv[1],R_OK)){
        fprintf(stderr,"File cannot be read\n");
        return 1;
    }
    if (access(argv[2],R_OK)){
        fprintf(stderr,"File cannot be read arg 2\n");
        return 1;
    }
    if ((strstr(argv[1],"activity"))){
        fprintf(stderr,"cannot have the activity file first");
        return 1;
    }

    /*now the proper code starts*/
    if (strstr(argv[1],"results")){
        readResults(argv[1],argv[2],argv[3]);
    }

    else {
        comStuResults(argv[1],argv[2],argv[3]);
    }

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

void readResults(char * resultsFileName,char * activityFileName,char * newResultsFile){
    int i,j,k,found;
    float total;
    FullStudentData * studentDataList;
    idScore * idScoreList;
    
    int nScores = countCommas(resultsFileName);
    int nStudents = countLines(resultsFileName);

    char line[256];
    FILE * filepointer = fopen(resultsFileName,"r");
    int col = 0;
    char * splitString;

    int activityLength = countLines(activityFileName);
    idScoreList = malloc(activityLength*sizeof(idScore));

/*setup the data structure with the right amnt of elements */
    studentDataList = malloc(nStudents*sizeof(FullStudentData));

    for (i=0;i<nStudents;i++){
        studentDataList[i].scores = malloc((nScores+1)*sizeof(float)); /*+1 to make sure there's enough space for the grade from new file to be entered*/
    }


/*Now need to look at the new */

    fgets(line,sizeof(line),filepointer);

    for (i=0;i<nStudents;i++){
        col = 1;
        fgets(line,sizeof(line),filepointer);
        splitString = strtok(line,",");
        
        studentDataList[i].id = atoi(splitString);
        col++;

        while ((splitString = strtok(NULL,","))!=NULL){

            if (col == 2){
                strcpy(studentDataList[i].lastName,splitString);
            }
            
            else if (col == 3){
                strcpy(studentDataList[i].firstName,splitString);
            }

            else if (col == 4){
                studentDataList[i].avgScore = atoi(splitString);
            }
            
            else if (col>4){
                studentDataList[i].scores[col-5] = atof(splitString);
            }

            col++;
        }

    } 

    fclose(filepointer); /* just for organisation */

    /*link fullstudentdata structure with the data in the activity file*/
    filepointer = fopen(activityFileName,"r");
    fgets(line,sizeof(line),filepointer); /*skip the header line*/
    i = 0;
    while (fgets(line,sizeof(line),filepointer)){
        sscanf(line,"%d,%d",&idScoreList[i].id,&idScoreList[i].score);
        i++;
    }

    for (i=0;i<nStudents;i++){
        found = 0;
        for (j=0;j<activityLength;j++){
            if (studentDataList[i].id == idScoreList[j].id){
                studentDataList[i].scores[nScores] = idScoreList[j].score;
                total = 0.0;
                /*just calculate the average of all the scores in a given student data element*/
                for (k=0;k<(nScores+1);k++){
                    total += studentDataList[i].scores[k];
                    
                }
                studentDataList[i].avgScore = total/(nScores+1);
                
                found = 1;
                break;

            }
        }

        if (!found){
            studentDataList[i].scores[nScores] = 0;
            total = 0.0;
            /*just calculate the average of all the scores in a given student data element*/
            for (k=0;k<(nScores+1);k++){
                total += studentDataList[i].scores[k];
                    
            }


            studentDataList[i].avgScore = total / (nScores+1); 
            
        }

    }


    fclose(filepointer);

    writeToFile(newResultsFile,studentDataList,nStudents,nScores+1);

/*free all data before func ends*/
    for (i=0;i<nStudents;i++){

        free(studentDataList[i].scores);
      
    }

    free(studentDataList);
    free(idScoreList);
}

int countCommas(char * filename){
    int count = 0;
    FILE * filepointer = fopen(filename,"r");

    char ch;

    while ((ch = fgetc(filepointer))!='\n'){
        if (ch == ','){
            count++;
        }
    }
    return count-3;
}

void comStuResults(char * studentsFileName,char * activityFileName,char * newResultsFile){
    int Nstudents = countLines(studentsFileName);
    int Nscores = countLines(activityFileName);
    idStudent * idStudentList;
    idScore * idScoreList;
    FullStudentData * studentDataList = malloc(Nstudents*sizeof(FullStudentData));
    int i;

    if (Nstudents <= 0 || Nscores <= 0){
        fprintf(stderr,"cannot have empty files");
        exit(1);
    }

    idStudentList = malloc(Nstudents*sizeof(idStudent));
    idScoreList = malloc(Nscores*sizeof(idScore));

    studentList_init(idStudentList,studentsFileName);
    scoreList_init(idScoreList,activityFileName);
    linkStudent2Score(idStudentList,idScoreList,Nstudents,Nscores,studentDataList);
    
    writeToFile(newResultsFile,studentDataList,Nstudents,1);

    for (i=0;i<Nstudents;i++){
        free(studentDataList[i].scores);
    }

    free(idStudentList);
    free(idScoreList);
    free(studentDataList);
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

void linkStudent2Score(idStudent * idStudentP,idScore * idScoreP, int nStudents,int nScores,FullStudentData * studentDataList){
    int i; /*look just iterate through until a match is found then break*/
    int j;
    int found; /*0 - false, 1 - true*/

    for (i=0;i<nStudents;i++){
        found = 0;
        for (j=0;j<nScores;j++){
            if (idScoreP[j].id == idStudentP[i].id){

                /*put in data struct*/
                studentDataList[i].id = idStudentP[i].id;
                strcpy(studentDataList[i].lastName,idStudentP[i].lastName);
                strcpy(studentDataList[i].firstName,idStudentP[i].firstName);
                studentDataList[i].avgScore = (float) idScoreP[j].score;
                studentDataList[i].scores = malloc(1*sizeof(float));
                studentDataList[i].scores[0] = idScoreP[j].score;

                found = 1;
                break;
            }
        
        }

        if (!found){
            studentDataList[i].id = idStudentP[i].id;
            strcpy(studentDataList[i].lastName,idStudentP[i].lastName);
            strcpy(studentDataList[i].firstName,idStudentP[i].firstName);
            studentDataList[i].avgScore = 0.0;
            studentDataList[i].scores = malloc(1*sizeof(float));
            studentDataList[i].scores[0] = 0.0;

 
        }
    }
    
}

void writeToFile(char * filename,FullStudentData * studentDataList, int nStudents, int nScores){
    FILE * filepointer = fopen(filename,"w");
    int i,j;

    fprintf(filepointer,"id,last_name,first_name,average");
    for (i=1;i<=nScores;i++){
        fprintf(filepointer,",grade");
        if (i<9){
            fprintf(filepointer,"0%d",i);
        }
        else{
            fprintf(filepointer,"%d",i);
        }
    }
    fprintf(filepointer,"\n");

    for (i=0;i<nStudents;i++){
        fprintf(filepointer,"%d,%s,%s,%.2f",studentDataList[i].id,studentDataList[i].lastName,studentDataList[i].firstName,studentDataList[i].avgScore);
        for (j=0;j<(nScores);j++){
            fprintf(filepointer,",%.0f",studentDataList[i].scores[j]);
        }
        fprintf(filepointer,"\n");
    }
    fclose(filepointer);

}