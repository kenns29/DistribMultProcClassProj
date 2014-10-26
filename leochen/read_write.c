#include "sem.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 2

extern TCB_t* RunQ;

int buff;

Sem_t* rsem;
Sem_t* wsem;
Sem_t* mutex;
int wc,rc,wwc,rwc;

int rid = 0;
int wid = 0;
int inc = 0;

void reader_func();
void writer_func();

int main(int argc, char** argv) {
    printf(" - - - - - - - - - - Readers and Writers - - - - - - - - - -\n");

    buff = 0;
    wc = rc = wwc = rwc = 0;

    rsem = CreateSem(0);
    wsem = CreateSem(0);
    mutex= CreateSem(1);

    InitQ(&RunQ);

    start_thread(reader_func);
    start_thread(reader_func);
    start_thread(reader_func);
    start_thread(writer_func);
    start_thread(writer_func);

    run();

    return 0;
}


void reader_entry() {
    P(mutex);
    if (wwc > 0 || wc > 0) {
        rwc++;
        V(mutex);
        P(rsem);
        rwc--;
    }
    rc++;
    if (rwc > 0) {
        V(rsem);
    } else {
        V(mutex);
    }
}

void reader_exit() {
    P(mutex);
    rc--;
    if (rc == 0 && wwc > 0) {
        V(wsem);
    } else {
        V(mutex);
    }
}

void writer_entry() {
    P(mutex);
    if (rc > 0 || wc > 0) {
        wwc++;
        V(mutex);
        P(wsem);
        wwc--;
    }
    wc++;
    V(mutex);
}

void writer_exit() {
    P(mutex);
    wc--;
    if (rwc > 0) {
        V(rsem);
    } else {
        if (wwc > 0) {
            V(wsem);
        } else {
            V(mutex);
        }
    }
}

void reader_func() {
    int id = rid++;
    while(1) {
        reader_entry();
        printf("reader %d: reads %d\n", id, buff);
        usleep(1000000);
        yield();
        reader_exit();
    }
}


void writer_func() {
    int id = wid++;
    while(1) {
        writer_entry();
        printf("writer %d: writes %d\n", id, inc);
        buff = inc++;
        usleep(1000000);
        yield();
        writer_exit();
    }
}
