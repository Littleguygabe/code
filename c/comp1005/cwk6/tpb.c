#include "queue.h"
#include "tpb.h"
#include <stdlib.h> /* you probably need this */
#include <stdio.h>  /* you definitely need this */
#include <ctype.h>
#include <string.h>

/* add other headers from the CSTDLIB needed */

/* define my boolean type */

#define true 1
#define false 0
typedef int bool;

#define FRAME_NUMBER 10 /* you may need this */

/* Accepted Tokens */
typedef enum {
  TOKEN_LITERAL,      /* Number 0-9 */
  TOKEN_SPARE,        /* / symbol */
  TOKEN_STRIKE,       /* X/x symbol */
  TOKEN_GUTTER,       /* - symbol */
  TOKEN_FAULT        /* F/f symbol */
} Token;

/* Struct for the lexical tokenization */
typedef struct
{
  Token token;
  char character;
  int lookahead;
  int pos;
} Lex;

/* I implement a few functions to help you */

void free_scoreboard(LinkedList * scoreboard)
{
  Node * next = scoreboard->head;
  while (next!=NULL)
  {
    free(next->data);
    next = next->next;
  }

  free_linked_list(scoreboard);
}

/* 
This function is not in the tpb.h, because it doesn't need to be externalised
Given a token of a roll, it return its value. prev_roll is the token of the
previous roll necessary to computer the spare
 */
int get_token_value(Lex* token, Lex * prev_roll)
{
  if (token!= NULL)
  {
    switch (token->token)
    {
      case TOKEN_STRIKE:
        return 10;
      case TOKEN_SPARE:
        if (prev_roll!= NULL)  return 10-get_token_value(prev_roll,NULL); 
        else break;
      case TOKEN_LITERAL:
        return token->character - '0';
      default: /* GUTTER / FAULT*/
        return 0;
    }

  }

  return -1; /* in case on an error */
}

/*
This function performs the tokenization
Also this one is not in the tpb.h as it's not needed to be seen outside

The purpose of this function is that, given a character, it makes the 
corresponding token. The struct Lex l is where the values are stored
because the function returns true in case of success, false otherwise.

*/

bool tokenization(char c, Lex *l)
{

    switch (c)
    {
      case 'x':
      case 'X':
        l->token = TOKEN_STRIKE;
        l->character = c;
        l->lookahead=2;
        break;
      case 'f':
      case 'F':
        l->token = TOKEN_FAULT;
        l->character = c;
        l->lookahead=0;
        break;
      case '-':
        l->token = TOKEN_GUTTER;
        l->character = c;
        l->lookahead=0;
        break;
      case '/':
        l->token = TOKEN_SPARE;
        l->character = c;
        l->lookahead=1; 
        break;
      default:
        if (isdigit(c) && (c!='0'))
        {
          l->token = TOKEN_LITERAL;
          l->character = c;
          l->lookahead=0;
        }
        else return false;
    }

    return true;
}

bool validateFrame(LinkedList *frame, int *err_position) {
    Lex* tokenArr[3] = {NULL, NULL, NULL};
    Node* curNode = frame->head;
    int i = 0;
    int size = 0;

    while (curNode && i < 3) {
        tokenArr[i] = (Lex*)(curNode->data);
        curNode = curNode->next;
        i++;
    }

    if (tokenArr[1] && tokenArr[1]->token == TOKEN_STRIKE && 
        (!tokenArr[0] || tokenArr[0]->token != TOKEN_STRIKE)) {
        *err_position = tokenArr[1]->pos;
        printf("1\n");
        return false;
    }

    if (tokenArr[0] && tokenArr[1] && 
        tokenArr[0]->token == TOKEN_STRIKE && tokenArr[1]->token == TOKEN_SPARE) {
        *err_position = tokenArr[1]->pos;
        printf("2\n");
        return false;
    }

    if (tokenArr[1] && tokenArr[2] && 
        tokenArr[1]->token == TOKEN_STRIKE && tokenArr[2]->token == TOKEN_SPARE) {
        *err_position = tokenArr[2]->pos;
        printf("3\n");
        return false;
    }

    curNode = frame->head;
    while (curNode) {
      size++;
      if (size > 3) {
        *err_position = ((Lex*)curNode->data)->pos-1;
        printf("4\n");
        return false;
      }
        curNode = curNode->next;
    }

    return true;
}


bool validateLastFrame(LinkedList *frame, int *err_position) {
    Lex* tokenArr[3] = {NULL, NULL, NULL};
    Node *curNode = frame->head;
    int i = 0;
    int size = 0;
    int strikeSpare = 0;

    while (curNode && i < 3) {
        tokenArr[i] = (Lex*)(curNode->data);
        curNode = curNode->next;
        i++;
    }

    curNode = frame->head;
    while (curNode) {
        size++;
        curNode = curNode->next;
    }

    if (tokenArr[1] != NULL && tokenArr[1]->token == TOKEN_STRIKE && tokenArr[0]->token != TOKEN_STRIKE) {
        *err_position = tokenArr[1]->pos;
        printf("5\n");
        return false;
    }

    if (tokenArr[0] != NULL && tokenArr[1] != NULL && tokenArr[0]->token == TOKEN_STRIKE && tokenArr[1]->token == TOKEN_SPARE) {
        *err_position = tokenArr[1]->pos;
        printf("6\n");
        return false;
    }

    if (tokenArr[1] != NULL && tokenArr[2] != NULL && tokenArr[1]->token == TOKEN_STRIKE && tokenArr[2]->token == TOKEN_SPARE) {
        *err_position = tokenArr[2]->pos;
        printf("7\n");
        return false;
    }

    if (tokenArr[0] != NULL && tokenArr[0]->token == TOKEN_STRIKE) {
        strikeSpare = 1;
    } else if (tokenArr[0] != NULL && tokenArr[0]->token != TOKEN_STRIKE && tokenArr[1] != NULL && tokenArr[1]->token == TOKEN_SPARE) {
        strikeSpare = 1;
    }

    if (!strikeSpare && size >= 3 && tokenArr[2] != NULL) {
        printf("8\n");
        *err_position = tokenArr[2]->pos;
        return false;
    }

    return true;
}


int getScore(Token T, Node* curNode){
  
  switch (T)
  {
  case TOKEN_LITERAL:
    return ((int)((Lex*)curNode->data)->character) - 48;

  case TOKEN_GUTTER:
  case TOKEN_FAULT:
    return 0;
  
  case TOKEN_STRIKE:
    return 10;

  case TOKEN_SPARE:
    if (curNode->prev) {
      return 10 - getScore(((Lex*)curNode->prev->data)->token, curNode->prev);
    } else {
        return 0; 
    }


  default:
    return 0;
  }
}

int getLLAsize(LinkedList **llarray, int arraySize) {
    int count = 0;
    int i;
    for (i = 0; i < arraySize; i++) {
        if (llarray[i] != NULL && llarray[i]->head != NULL) {
            count++;
        }
    }
    return count;
}


LinkedList * bowling_score_parser(const char *game_characters, int *err_position)
{

    /* initialzation */
  LinkedList * scoreboard = initialise_linked_list();
  Queue * tokenQ = initialise_queue();
  int i,j;
  LinkedList * frame_list[FRAME_NUMBER];
  Lex * templex;

  Lex * curToken;


  int count=0;

  Node * curNode;
    /* Lexer */

  Frame * tempFrame;
  int cumScore=0;
  int pos =0;
  int frameScore=0;
  int strikeFound;
  char curChar;


  for (i=0;i<strlen(game_characters);i++){
    templex = (Lex*)malloc(sizeof(Lex));
    if (tokenization(game_characters[i],templex)){
      templex->pos = i;
      push_queue(tokenQ,templex,sizeof(Lex));
    }
    else{
      free(templex);
      free_queue(tokenQ);
      free_scoreboard(scoreboard);
      *err_position = i;
      return NULL;
    }
    
  }  

    /* parser */

  for (i=0;i<FRAME_NUMBER;i++){
    frame_list[i] = initialise_linked_list();
  }
   
  i=0;


  while (tokenQ->head&&(i/2)<10){ 
    curToken = (Lex *)pop_queue(tokenQ);

    append_linked_list(frame_list[i/2],curToken);

    if (curToken->token == TOKEN_STRIKE || curToken->token == TOKEN_SPARE){
      for (j=1;j<(curToken->lookahead)+1;j++){
        if (game_characters[curToken->pos+j]){
          templex = (Lex*)malloc(sizeof(Lex));
          tokenization(game_characters[curToken->pos+j],templex);
          
          templex->pos = curToken->pos+j;
          append_linked_list(frame_list[i/2],templex);
          
        }
        else{
          break;
        }
      }
     
    }
     
    if (curToken->token==TOKEN_STRIKE){i++;}

    i++;
    count++;
  } 


    /* reducer */
  /* just prints every item in the array of linked lists for checking*/
  /*
  for (i=0;i<FRAME_NUMBER;i++){
    printf("list %d",i);
    curNode = frame_list[i]->head;
    while (curNode){
      printf(" -> %c",((Lex*)curNode->data)->character);
      curNode=curNode->next;
    }
    printf("\n");
  }
  */
  
  /*validate all but last frame*/
  for (i=0;i<getLLAsize(frame_list,FRAME_NUMBER)-1;i++){
    if (!validateFrame(frame_list[i],err_position)){
      free(templex);
      free_queue(tokenQ);
      
      free_scoreboard(scoreboard);
      return NULL;
    }
  }

  /*validate last frame*/
  if (!validateLastFrame(frame_list[getLLAsize(frame_list,FRAME_NUMBER)-1],err_position)){
    free(templex);
    free_queue(tokenQ);
    
    free_scoreboard(scoreboard);
    return NULL;
  }
  /*if (strlen(game_characters)!=count){
    free_queue(tokenQ);
    free(templex);
    free(scoreboard);
    *err_position = count;
    return NULL;
  }
  */
  for (i=0;i<FRAME_NUMBER;i++){
    pos=0;
    frameScore=0;
    strikeFound = 0;
    tempFrame = malloc(sizeof(Frame));
    curNode = frame_list[i]->head;
    while (curNode){
      if (!strikeFound){
        curChar = ((Lex*)curNode->data)->character;
        tempFrame->rolls[pos] = curChar;
        pos++;
        if ((curChar == 'S'||curChar=='s')){
          strikeFound=1;
        }

      }
      if (curChar){
        frameScore+=getScore(((Lex*)curNode->data)->token,curNode);
      }
      curNode = curNode->next;
    }

    cumScore+=frameScore;

    if (pos==0){
      break;
    }
    tempFrame->score = cumScore;


    tempFrame->n_rolls = pos;

    append_linked_list(scoreboard,tempFrame);
  }


  while(!scoreboard->tail->data){
    remove_tail_linked_list(scoreboard);
  }

    /* Garbage collection */


  
  for(i=0;i<FRAME_NUMBER;i++){
    free_linked_list(frame_list[i]);
  }

  free_queue(tokenQ);
  free(templex);

  return scoreboard;

}

void printBasicBoard(LinkedList*scoreboard){
  Node * curNode = scoreboard->head;
  int i;
  Frame* frameNode;
  while(curNode!=NULL&&curNode!=scoreboard->tail){
    frameNode = ((Frame*)curNode->data);


    printf("%c",frameNode->rolls[0]);
    
    if (frameNode->n_rolls>1){
      if (frameNode->rolls[1]=='/'){
        printf("/");
      }
    }

    if (frameNode->n_rolls==2){
      printf("%c",frameNode->rolls[1]);
    } 
    curNode = curNode->next;
  }

  frameNode=((Frame*)scoreboard->tail->data);
  if(frameNode->n_rolls>0){
    for (i=0;i<frameNode->n_rolls;i++){
      printf("%c",frameNode->rolls[i]);
    }
  }

  printf(":");
  curNode=scoreboard->head;
  while (curNode!=NULL)
  {
    frameNode = ((Frame*)curNode->data);
    printf(" %d",frameNode->score);
    curNode = curNode->next;
  }
  printf("\n");
}

void printAdvScoreboard(LinkedList*scoreboard){
  int i,j;
  Node* curNode;
  Frame* curFrame;
  int localRolls;
  int frameCount=0;

  int borderLen = 41;
  int padBuff = 0;
  int scoreLength=0;

  curNode = scoreboard->head;
  while(curNode){
    scoreLength++;
    curNode=curNode->next;
  }


  if (((Frame*)scoreboard->tail->data)->n_rolls<3 && scoreLength==10){
    padBuff = 2;
  }
  

  printf("+");
  for (i=0;i<borderLen;i++){
    printf("-");
  }
  printf("+\n");

  curNode=scoreboard->head;
  while (curNode!=scoreboard->tail)
  {
    frameCount++;
    printf("|");
    curFrame = ((Frame*)curNode->data);
    if (curFrame->rolls[0]=='X'||curFrame->rolls[0]=='x'){
      localRolls = 1;
    }

    else if(curFrame->rolls[1]=='/'){
      localRolls=2;
    }

    else{
      localRolls=curFrame->n_rolls;
    }


    for (i=0;i<localRolls;i++){
      printf("%c",curFrame->rolls[i]);
      if (i!=localRolls-1){
        printf(" ");
      }
    }
    
    for (i=0;i<(3-localRolls-1)*2;i++){
      printf(" ");
    }

    curNode=curNode->next;
  }

  /*print last frame*/
  curFrame = (Frame*)scoreboard->tail->data;
  printf("|");
  for (i=0;i<curFrame->n_rolls;i++){
    
    printf("%c",curFrame->rolls[i]);



    if (curFrame->n_rolls==1){
      for (j=0;j<(3-curFrame->n_rolls);j++){
        printf(" ");
      }
    }
    if (i!=curFrame->n_rolls-1){
      printf(" ");
    }
  }
  frameCount++;

 /*change made*/
/*
  if (frameCount!=10&&curFrame->rolls[0]=='X'&&curFrame->n_rolls <3){
    printf(" ");
  }
*/
  for (i=0;i<(FRAME_NUMBER-frameCount-1);i++){
    printf("|   ");
  }

  if (frameCount<FRAME_NUMBER){
    printf("|     ");
  }

  for (i=0;i<padBuff;i++){
    printf(" ");
  }

  printf("|\n");

  curNode = scoreboard->head;
  while (curNode!=scoreboard->tail){
    curFrame = (Frame*)curNode->data;
    printf("|%3d",curFrame->score);
    curNode = curNode->next;
  }
  if (frameCount!=FRAME_NUMBER){
    printf("|%3d",((Frame*)scoreboard->tail->data)->score); 
  }
  else{
    printf("|%5d",((Frame*)scoreboard->tail->data)->score);
    
  }

  for (i=0;i<(FRAME_NUMBER-frameCount-1);i++){
    printf("|   ");
  }

  if (frameCount<FRAME_NUMBER){
    printf("|     ");
  }

  printf("|\n");

  printf("+");
  for (i=0;i<borderLen;i++){
    printf("-");
  }
  printf("+\n");

}

void print_scoreboard(LinkedList*scoreboard)
{ 

  #ifdef SCOREBOARD
  printAdvScoreboard(scoreboard);

  #else
  printBasicBoard(scoreboard);

  #endif

}