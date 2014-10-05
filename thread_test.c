/* *****************
 * Homework 1      *
 * Hong Xiang Wang *
 * Lei Chen        *
 *******************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define FALSE 0
#define TRUE 1
#include "threads.h"

extern TCB_t *runQ;
void *function1();
void *function2();
void *function3();

int global = 1;
int main(int argc, char **argv){
  InitQ(&runQ);
  start_thread((void*)function1);
  start_thread((void*)function2);
  start_thread((void*)function3);
  
  run();
  return 0;
}

void *function1(){
  int local = 1;
  while(TRUE){
    printf("In thread 1\n");
    printf("\t the global value = %d\n", global++);
    printf("\t increment global value by one\n");
    printf("\t -----------------------------\n");
    printf("\t the local value = %d\n", local++);
    printf("\t increment local value by one\n");
    printf("#############################################\n");
    usleep(1000000);
    yield();
  }
}

void *function2(){  
  int local = 1;
  while(TRUE){
    printf("In thread 2\n");
    printf("\t the global value = %d\n", global++);
    printf("\t increment global value by one\n");
    printf("\t -----------------------------\n");
    printf("\t the local value = %d\n", local++);
    printf("\t increment local value by one\n");
    printf("#############################################\n");
    usleep(1000000);
    yield();
  }
}

void *function3(){
  int local = 1;
  while(TRUE){
    printf("In thread 3\n");
    printf("\t the global value = %d\n", global++);
    printf("\t increment global value by one\n");
    printf("\t -----------------------------\n");
    printf("\t the local value  = %d\n", local++);
    printf("\t increment local value by one\n");
    printf("#############################################\n");
    usleep(1000000);
    yield();
  }
}
