#include "sem.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 2

extern TCB_t* RunQ;

int buff[BUFFER_SIZE] = {0};
int in;
int out;
Sem_t* full;
Sem_t* empty;
Sem_t* mutex;

void producerFunc();
void consumerFunc();

int main(int argc, char** argv) {
    printf(" - - - - - - - - - - Test 2 - - - - - - - - - -\n");

    in = 0;
    out = 0;
    full = CreateSem(BUFFER_SIZE);
    empty = CreateSem(0);
    mutex = CreateSem(1);

    printf("full->count = %d\n", full->count);
    printf("empty->count = %d\n", empty->count);

    InitQ(&RunQ);

    start_thread(producerFunc);
    start_thread(consumerFunc);

    run();

    return 0;
}

int item = 0;
int gid = 0;

void producerFunc() {
    int id = gid++;
    while(1) {
        P(full);
        P(mutex);

        buff[in] = item;
        printf("p %d: item %d ----> slot %d\n",id, item, in);
        item++;
        in = (in + 1) % BUFFER_SIZE;
        usleep(1000000);

        V(mutex);
        V(empty);

        yield();
    }
}

void consumerFunc() {
    int id = gid++;
    int result;
    while(1) {
        P(empty);
        P(mutex);

        result = buff[out];
        printf("c %d: item %d <---- slot %d\n",id, result, out);
        out = (out + 1) % BUFFER_SIZE;
        usleep(1000000);

        V(mutex);
        V(full);

        yield();
    }
}

