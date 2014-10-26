#include "q.h"
#include <stdio.h>

TCB_t* RunQ;

void start_thread(void (*function)(void)) {
    TCB_t* tcb;
    void* stack;

    tcb= (TCB_t*)malloc(sizeof(TCB_t));
    stack = malloc(STACK_SIZE);

    init_TCB (tcb, function, stack, STACK_SIZE);
    printf("New TCB: [%d]\n", (int)tcb);

    AddQ(&RunQ, tcb);
}

void run() {
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    printf("start thread: [%d]\n", (int)RunQ);
    swapcontext(&parent, &(RunQ->context));  // start the first thread
}

void yield() {
    RotateQ(&RunQ);
    //printf("swap thread: from [%d] to [%d]\n", (int)(RunQ->prev), (int)RunQ);
    swapcontext(&(RunQ->prev->context), &(RunQ->context));  // start the first thread
}
