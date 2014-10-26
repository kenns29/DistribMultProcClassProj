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
    //printf("mark p1\n");
    sem->count--;
    //printf("mark p2, count = %d\n", sem->count);
    if (sem->count < 0) {

        //printf("mark p3\n");
        //PrintQ(&RunQ);
        //PrintQ(&(sem->q));

        TCB_t* cur = DelQ(&RunQ, 0);

        //printf("mark p4\n");
        //PrintQ(&RunQ);
        //PrintQ(&(sem->q));

        AddQ(&(sem->q), cur);

        //printf("mark p5\n");
        //PrintQ(&RunQ);
        //PrintQ(&(sem->q));

        swapcontext(&(cur->context), &(RunQ->context));
        //printf("mark p6\n");
    }
    //printf("mark p7\n");
}

// increments the semaphore, and if the value is 0 or negative, 
// then takes a PCB out of the semaphore queue and puts it into the run queue. 
// and then yields to the next runnable process
void V(Sem_t * sem)  {
    sem->count++;
    //printf("mark v1, count = %d\n", sem->count);
    if (sem->count <= 0) {
        //printf("mark v2\n");
        TCB_t* wakenUp = DelQ(&(sem->q), 1);
        //printf("mark v3, wakenup = %d\n", (int)wakenUp);
        //PrintQ(&RunQ);
        //PrintQ(&(sem->q));

        AddQ(&RunQ, wakenUp);

        //printf("mark v4\n");
        //PrintQ(&RunQ);
        //PrintQ(&(sem->q));

        //printf("mark v5\n");
        yield();
        //printf("mark v6\n");
    }
}
