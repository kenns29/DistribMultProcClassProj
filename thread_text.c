#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
  printf("In thread 1\n");
  yield();
}

void *function2(){
  printf("In thread 2\n");
  yield();
}

void *function3(){
  printf("In thread 3\n");
  yield();
}
