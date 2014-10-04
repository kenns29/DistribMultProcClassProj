#include "q.h"

const size_t STACK_SIZE = 8192;
TCB_t *runQ;

void start_thread(void (*function)(void)){
  void *stack = malloc(STACK_SIZE);
  TCB_t *tcb = new_TCB();
  init_TCB(tcb, function, stack, STACK_SIZE); 
  AddQ(&runQ, tcb);
}

void run(){
  ucontext_t parent;
  getcontext(&parent);
  swapcontext(&parent, &(runQ->context));
}

void yield(){
  RotateQ(&runQ);
  swapcontext(&(runQ->pre->context), &(runQ->context));
}
