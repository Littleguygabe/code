#include <stdio.h>
#include <stdlib.h>



typedef struct Node
{
    struct Node *next;  /*the variable 'next' is a pointer to data type , if NULL indicates it is an oprhan node*/
    int data;
    /*add a tail pointer if want to do circular linked list - then update everytime a new element is */
}Node;
/* ^^ general structure for a node ^^ */

typedef struct LinkedList{
    Node *head;
    /*can make circular by adding a tail var that gets updated everytime a new variable is added -- maintains O(1) time cpmlx */
}LinkedList;

LinkedList * list_init(void);
Node * node_init(int val);
void addNode(LinkedList * list, Node * node);
Node * getNode(LinkedList * list, int index);

int main (int argc, char *argv[]) {
    Node *node = node_init(1);
    LinkedList * list = list_init();

    Node * targettedNode;
    Node *cur;

    int i;
    
    list->head = node; /*necessary for the list to work*/

    for (i=1;i<10;i++){
        addNode(list,node_init(i+1));
    }
    
    i=5;
    printf("node %d data --> %d",i,getNode(list,i)->data);
    return 0;
}

LinkedList * list_init(void){
    LinkedList *list;
    list = (LinkedList *) malloc(sizeof(LinkedList)); /*allocates the memory needed for the linked list head then assigns the pointer to that allocated memory to the variable list*/

    return list;

}

Node * node_init(int val){
    Node * node;
    node = (Node *) malloc(sizeof(Node)); /*assigns the memory needed for the node --> could be done through a function -- doesnt need type cast as returns void* but good practice*/
    node->next = NULL; /*Just to -1 as good practice -- -NULL indicates tail/orphan node*/
    node->data = val;

    return node;
}

void addNode(LinkedList * list, Node * node){

    if ((list->head) == NULL){
        list->head = node;
    }
    else{
        Node * cur = list->head;
        while (cur){
            if (cur->next == NULL){
                break;
            }

            cur = cur->next;

        }

        cur->next = node;
    }
}

Node * getNode(LinkedList * list, int index){
    int count = 1;
    Node * cur = list-> head;
    while (count!=index){
        cur = cur->next;
        count++;
    }

    return cur;
}