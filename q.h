#include "TCB.h"
#ifndef RUNQ
#define RUNQ
#include <stdlib.h>
#include <stdio.h>
#endif

/****************
 * RunQ Class ***
 ****************/
typedef struct{
 struct  TCB_t *head;
}RunQ;


RunQ *new_RunQ(){
  RunQ *newRunQ = (RunQ*)malloc(sizeof(RunQ));
  newRunQ-> head = NULL;
  return newRunQ;
}
void InitQ(TCB_t ** head){
  *head = NULL;
}

void AddQ(TCB_t ** head, TCB_t *item){
  if((*head) == NULL){
    (*head) = item;
  }
  else if((*head)->pre != NULL){
    TCB_t *temp = (*head)->pre;
    (*head)->pre = item;
    (*head)->pre->next = (*head);
    (*head)->pre->pre = temp;
    temp->next = (*head)->pre;
  }
  else{
    (*head)->pre = item;
    (*head)->pre->next = (*head);
    (*head)->next = (*head)->pre;
    (*head)->pre->pre = (*head);
  }
}

TCB_t* DelQ(TCB_t ** head){
  TCB_t *temp = NULL;
  if((*head)==NULL){
    return (*head);
  }
  else if((*head)->pre == NULL && (*head)->next == NULL){
    temp = (*head);
    //(*head) = NULL;
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

void RotateQ(TCB_t **head){
  if((*head)->next != NULL && (*head)->pre != NULL){
    (*head) = (*head)->next;
  }
}



