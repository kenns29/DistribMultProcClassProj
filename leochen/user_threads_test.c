#include <stdio.h>
#include "threads.h"


extern TCB_t * RunQ;

void func1();
void func2();
void func3();

int main(int argc, char** argv) {
    InitQ(&RunQ);

    start_thread(func1);
    start_thread(func2);
    start_thread(func3);

    run();

    return 0;
}

int global = 0;

void func1() {
    int local = 0;
    while(1) {
        //PrintQ(&RunQ);
        printf("this is function 1: local = %d, global = %d\n", local++, global++);
        usleep(1000000);
        yield();
    }
}

void func2() {
    int local = 0;
    while(1) {
        //PrintQ(&RunQ);
        printf("this is function 2: local = %d, global = %d\n", local++, global++);
        usleep(1000000);
        yield();
    }
}

void func3() {
    int local = 0;
    while(1) {
        //PrintQ(&RunQ);
        printf("this is function 3: local = %d, global = %d\n", local++, global++);
        usleep(1000000);
        yield();
    }
}
