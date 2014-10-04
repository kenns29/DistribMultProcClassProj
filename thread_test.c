#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define FALSE 0
#define TRUE 1
#include "threads.h"

void *function1();
void *function2();
void *function3();

int main(int argc, char **argv){
  start_thread((void*)function1);
  start_thread((void*)function2);
  start_thread((void*)function3);
  
  run();
  return 0;
}

void *function1(){
  while(TRUE){
    printf("In thread 1\n");
    usleep(1000000);
    yield();
  }
}

void *function2(){
  while(TRUE){
    printf("In thread 2\n");
    usleep(1000000);
    yield();
  }
}

void *function3(){
  while(TRUE){
    printf("In thread 3\n");
    usleep(1000000);
    yield();
  }
}
