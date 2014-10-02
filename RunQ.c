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
}RunQ;

RunQ *new_RunQ(){
  RunQ *newRunQ = (RunQ*)malloc(sizeof(RunQ));
  newRunQ-> head = NULL;
  return newRunQ;
}
void InitQ(Node* head){
  if(head == NULL){
    head = new_Node(0); 
  }
}

void AddQ(Node* head, int *item){
  if(head == NULL){
    head = new_Node(*item);
  }
  else if(head->pre != NULL){
    Node *temp = head->pre;
    head->pre = new_Node(*item);
    head->pre->next = head;
    head->pre->pre = temp;
    temp->next = head->pre;
  }
  else{
    head->pre = new_Node(*item);
    head->pre->next = head;
    head->next = head->pre;
    head->pre->pre = head;
  }
}
int main(int argc, char**argv){

  return 0;
}
