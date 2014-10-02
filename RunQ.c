#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/******************
 * The Node Class *
 ******************/
typedef struct{
  int item;
  struct Node * pre;
  struct Node * next;
}Node;


Node* new_empty_Node(){
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode-> item = 0;
  newNode-> pre = NULL;
  newNode-> next = NULL;
  
  return newNode;
}

Node* new_Node(int item){
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->item = item;
  newNode->pre = NULL;
  newNode->next = NULL;

  return newNode;
}

/****************
 * RunQ Class ***
 ****************/
typedef struct{
  Node *head;
  Node *tail;
}RunQ;

RunQ *new_RunQ(){
  RunQ *newRunQ = (RunQ*)malloc(sizeof(RunQ));
  newRunQ-> head = NULL;
  newRunQ-> tail = NULL;

  return newRunQ;
}
void InitQ(Node* head){
  if(head == NULL){
    head = new_Node(0); 
  }
}

void AddQ(Node* head, int *item){
  
}
int main(int argc, char**argv){

  return 0;
}
