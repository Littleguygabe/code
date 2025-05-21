#include "sort.h"
#include <string.h>
#include <stdlib.h>

/*only needed to print for debugging*/
#include <stdio.h>

/* sort linked list *list using merge insertion sort. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */

void insertNode(LinkedList *list,void *data, Node * nodeB){
    
    Node * tempNode = initialise_node();
    tempNode -> data = data;
    tempNode -> next = nodeB; 
    if (nodeB == list->head){
        list->head = tempNode;
        nodeB->prev = tempNode;
    }
    else{
        tempNode->prev = nodeB->prev;
        nodeB->prev->next = tempNode;
        nodeB->prev = tempNode;
        
    }

}

int compareData(void * Adata, void * Bdata){
    char * Astring = ((char *) Adata);
    char * Bstring = ((char *)Bdata);

    int result = strcmp(Astring,Bstring);

    if (result<0){
        return 1;
    }

    else{
        return 0;
    }
}

void insertion_sort(LinkedList *list, int (*compare)(void *, void *))
{
    
    LinkedList * B = initialise_linked_list();
    Node * node = list -> head;
    Node * nodeB;

    append_linked_list(B,node->data);
    remove_head_linked_list(list);

    while(list->tail!=NULL){
        nodeB = B->head;

        while (nodeB){
            if (compareData(list->head->data,nodeB->data)){
                insertNode(B,list->head->data,nodeB);                
                remove_head_linked_list(list);


                break;
            }
            nodeB = nodeB->next;
        }
        if (!nodeB){
            append_linked_list(B,list->head->data);
            remove_head_linked_list(list);
        }

    }

    list->head = B->head;
    list->tail = B->tail;
    free(B);
}

/* sort linked list *list using merge sort algorithm. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */

Node * copyNode(Node * node2copy){
    Node * newNode = initialise_node();
    /*newNode->data = node2copy->data;
    newNode->next=node2copy->next;
    newNode->prev = node2copy->prev;*/

    newNode->data = malloc(strlen((char *)node2copy->data));
    strcpy((char *) newNode->data,(char *)node2copy->data);
    newNode->next = NULL; 
    newNode->prev = NULL; 

    return newNode;    
}

void copyArray(LinkedList * A,LinkedList * B){    
    Node * cur = A->head; 
    Node * newNode;
    Node * lastNodeInB;
    B->head = copyNode(cur);

    lastNodeInB = B->head;
    cur = cur->next;

    while (cur){
        newNode = copyNode(cur);
        lastNodeInB->next = newNode;
        newNode->prev = lastNodeInB;
        
        lastNodeInB = newNode;
        
        cur = cur->next;
    }
  
}

void * getDataVal(LinkedList * list, int index){
    
    int count = 1;
    char * dataString;
    Node * cur = list->head;

    index++;

    while (cur){
        if (count == index){
            dataString = (cur->data);
            return dataString;
        }

        cur=cur->next;
        count++;
    }

    return "Null";
}



void copyData(LinkedList * ogList, int ogIndex, LinkedList * newlist, int newIndex){
    /*void * data = getDataVal(ogList,ogIndex);
    Node * cur = newlist->head;
    int count = 0;

    void * newData = malloc(100);
    strcpy(newData,data);

    while (cur){
        if (count==newIndex){
            cur->data = newData;
            return;
        }

        count++;
        cur = cur->next; 
    }*/
    Node * ogNode = ogList->head;
    Node * newNode = newlist->head;
    int ogcount = 0;
    int newcount = 0;

    while (ogNode && ogcount<ogIndex){
        ogNode = ogNode->next;
        ogcount++;
    }

    while (newNode && newcount<newIndex){
        newNode = newNode->next;
        newcount++;
    }

    if (ogNode->data){
        free(newNode->data);
        newNode->data = malloc(strlen((char *)ogNode->data)+1);
        strcpy((char *)newNode->data,(char *)ogNode->data);
    }

}

void topDownMerge(LinkedList * B, int iBegin, int iMiddle,int iEnd,LinkedList * A){
    int i = iBegin;
    int j = iMiddle;
    int k;

    for (k=iBegin;k<iEnd;k++){
        if (i<iMiddle&&(j>=iEnd||strcmp((char *)getDataVal(A,i),(char *)getDataVal(A,j))<=0)){
            /*B[k] = A[i]*/
            copyData(A,i,B,k);
            i++;
        }else{
            /*b[k] = A[j]*/
            copyData(A,j,B,k);
            j++;
        }
    }

}

void topDownSplitMerge(LinkedList * B,int iBegin, int iEnd,LinkedList * A){
    int iMiddle;

    if (iEnd-iBegin<=1){
        return;
    }

    iMiddle = (iEnd+iBegin)/2;

    topDownSplitMerge(A,iBegin,iMiddle,B);
    topDownSplitMerge(A,iMiddle,iEnd,B);

    topDownMerge(B,iBegin,iMiddle,iEnd,A);
}

int getListSize(LinkedList * list){
    int count = 0;
    Node * cur = list->head;
    while (cur){
        cur = cur->next;
        count++;
    }
    
    return count;
}

void freeData(LinkedList * list){
    Node * cur = list->head;
    while(cur){
        free(cur->data);
        cur = cur->next;
    }
}

void merge_sort(LinkedList *list, int (*compare)(void *, void *))
{
    
    LinkedList * B = initialise_linked_list();
    copyArray(list,B);
    topDownSplitMerge(list,0,getListSize(list),B);

    freeData(B);
    free_linked_list(B);
    
    
}



