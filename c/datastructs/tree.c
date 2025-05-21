#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node * right;
    struct Node * left;


}Node;

typedef struct tree
{
    Node *root;
}tree;

tree * tree_init(void);
Node * node_init(int data);
void insertNode(tree * Btree, Node * node2insert, Node * parent,int side);
void preOrderTraversal(Node * root);

int main (int argc, char *argv[]) {
    
    tree *bTree = tree_init();
    Node * rootNode;


    bTree->root = node_init(1);

    rootNode = bTree->root;

    insertNode(bTree,node_init(2),rootNode,0);
    insertNode(bTree,node_init(3),rootNode,1);
    insertNode(bTree,node_init(4),rootNode->left,0);
    insertNode(bTree,node_init(7),rootNode->left->left,0);
    insertNode(bTree,node_init(5),rootNode->left,1);

    insertNode(bTree,node_init(6),rootNode->right,1);
    insertNode(bTree,node_init(8),rootNode->right->right,0);
    insertNode(bTree,node_init(9),rootNode->right->right,1);

    /*setting up the tree */

    preOrderTraversal(rootNode);

    return 0;
}

tree * tree_init(void){
    tree * Btree;
    Btree = (tree *) malloc(sizeof(tree));

    return Btree;
}

Node * node_init(int data){
    Node * node;

    node =(Node *) malloc(sizeof(Node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}


void insertNode(tree * Btree, Node * node2insert, Node * parent,int side){
    /*side = 0 is left | side = 1 is right*/

    if (side){
        parent->right = node2insert;
    }

    else{
        parent->left = node2insert;
    }
}

void preOrderTraversal(Node * root){
    if (root!=NULL){
        printf("%d ",root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}