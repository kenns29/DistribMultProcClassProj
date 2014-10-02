#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/******************
 * The Node Class *
 ******************/
struct Node{
  int item;
  struct Node * pre;
  struct Node * next;
};


struct Node* new_empty_Node(){
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode-> item = 0;
  newNode-> pre = NULL;
  newNode-> next = NULL;
  
  return newNode;
}

struct Node* new_Node(int item){
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->item = item;
  newNode->pre = NULL;
  newNode->next = NULL;

  return newNode;
}

/****************
 * RunQ Class ***
 ****************/
typedef struct{
 struct  Node *head;
}RunQ;

RunQ *new_RunQ(){
  RunQ *newRunQ = (RunQ*)malloc(sizeof(RunQ));
  newRunQ-> head = NULL;
  return newRunQ;
}
void InitQ(struct Node* head){
  if(head == NULL){
    head = new_Node(0); 
  }
}

void AddQ(struct Node* head, int *item){
  if(head == NULL){
    head = new_Node(*item);
  }
  else if(head->pre != NULL){
    struct Node *temp = head->pre;
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
