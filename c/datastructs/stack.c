#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int data;
    struct node * next;
}node;

typedef struct linkedList
{
    node * head;
}linkedList;

linkedList * list_init(void);
node * node_init(int val);

/*stack functions*/
void push(linkedList * list, node * element);
node * pop(linkedList * list);

void printList(linkedList * list);

int main (int argc, char *argv[]) {
    int i;

    linkedList * list = list_init();

    for (i=0;i<10;i++){
        push(list,node_init(i));
    }
    printf("%d\n",pop(list)->data);
    printList(list);


    return 0;

}

linkedList * list_init(void){
    linkedList * list;
    list = malloc(sizeof(linkedList));
    list->head = NULL;

    return list;
}

node * node_init(int val){
    node * New_node;
    New_node = (node *) malloc(sizeof(node));
    New_node->next = NULL;
    New_node->data = val;

    return New_node;
}

void push(linkedList * list, node * element){
    /*push to tail and pop from tail*/

    node * cur;

    if ((list->head)==NULL){
        list->head = element;
    }

    else{
        element->next = list->head;
        list->head = element;
    }

}

void printList(linkedList * list){
    node * cur = list->head;
    while (cur){
        printf("%d ",cur->data);
        cur = cur->next;
    }
}
node * pop(linkedList * list){
    node * temp = list->head;
    list->head = temp->next;
    return temp;
}