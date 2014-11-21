#include "threads.h"

extern TCB_t* RunQ;

typedef struct Semaphore {
    int count;
    TCB_t* q;
} Sem_t;

// mallocs a semaphore structure, initializes it to the InitValue and returns the pointer to the semaphore.
Sem_t* CreateSem(int value) {
    Sem_t* ret = (Sem_t*)malloc(sizeof(Sem_t));
    ret->count = value;
    InitQ(&(ret->q));
    return ret;
}
// takes a pointer to a semaphore and performs P, i.e. decrements the semaphore
// if the value is less than zero then blocks the process in the queue associated with the semaphore.
void P(Sem_t* sem)  {
    sem->count--;
    if (sem->count < 0) {
        TCB_t* cur = DelQ(&RunQ, 0);
        AddQ(&(sem->q), cur);
        swapcontext(&(cur->context), &(RunQ->context));
    }
}

// increments the semaphore, and if the value is 0 or negative, 
// then takes a PCB out of the semaphore queue and puts it into the run queue. 
// and then yields to the next runnable process
void V(Sem_t * sem)  {
    sem->count++;
    if (sem->count <= 0) {
        TCB_t* wakenUp = DelQ(&(sem->q), 1);
        AddQ(&RunQ, wakenUp);
        yield();
    }
}
