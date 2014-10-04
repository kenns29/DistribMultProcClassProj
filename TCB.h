#ifndef TCB_HEADER
#define TCB_HEADER
#include <ucontext.h>
#include <stdlib.h>
#include <string.h>
#endif

typedef struct TCB{
  struct TCB *next;
  struct TCB *pre;
  ucontext_t context;
}TCB_t;

void init_TCB(TCB_t *tcb, void *function, void *stackP, int stack_size){
  memset(tcb, '\0', sizeof(TCB_t));
  getcontext(&tcb->context);
  tcb->context.uc_stack.ss_sp = stackP;
  tcb->context.uc_stack.ss_size = (size_t) stack_size;
  makecontext(&tcb->context, function, 0);
}

TCB_t *new_TCB(){
  TCB_t *tcb = (TCB_t*)malloc(sizeof(TCB_t));
  tcb->next = NULL;
  tcb->pre = NULL;
}
