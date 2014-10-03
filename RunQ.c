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
void InitQ(struct Node** head){
   *head = new_Node(0); 
}

void AddQ(struct Node** head, int item){
  if((*head) == NULL){
    (*head) = new_Node(item);
  }
  else if((*head)->pre != NULL){
    struct Node *temp = (*head)->pre;
    (*head)->pre = new_Node(item);
    (*head)->pre->next = (*head);
    (*head)->pre->pre = temp;
    temp->next = (*head)->pre;
  }
  else{
    (*head)->pre = new_Node(item);
    (*head)->pre->next = (*head);
    (*head)->next = (*head)->pre;
    (*head)->pre->pre = (*head);
  }
}

struct Node* DelQ(struct Node ** head){
  struct Node *temp = NULL;
  if((*head)->pre == NULL && (*head)->next == NULL){
    temp = (*head);
    (*head)->pre = (*head)->next = NULL;
  }
  else if((*head)->pre == (*head)-> next){
    temp = (*head);
    (*head) = (*head)->next;
    (*head)->pre = (*head)->next = NULL;
    temp->pre = temp->next = NULL;
  }
  else{
    temp = (*head);
    (*head) = (*head)->next;
    (*head)->pre = temp->pre;
    temp->pre->next = (*head);
    temp->next = temp->pre = NULL;
  }

  return temp;
}

void RotateQ(struct Node **head){
  if((*head)->next != NULL && (*head)->pre != NULL){
    (*head) = (*head)->next;
  }
}
int main(int argc, char**argv){
  RunQ *runQ = new_RunQ();
  InitQ(&runQ->head);
  
  int i;
  for(i = 1; i < 10; i++){
    AddQ(&runQ->head, i);
  }
  
  struct Node *iter;
  i = 0;
  
  for(iter = runQ->head, i=0; i<10; iter = iter->next){
    if(iter != NULL)
      printf("%d\n", iter->item);
    ++i;
  }

  struct Node* temp = DelQ(&runQ->head);

  printf("deleted value = %d\n", temp->item);

  for(iter = runQ->head, i=0; i<10; iter = iter->next){
    if(iter != NULL)
      printf("%d\n", iter->item);
    ++i;
  }
  
  RotateQ(&runQ->head);
  printf("After Rotation\n");
  for(iter = runQ->head, i=0; i<10; iter = iter->next){
    if(iter != NULL)
      printf("%d\n", iter->item);
    ++i;
  }
  return 0;
}
