// Project 4 submission
// Group members: 
//   1. Hongxiang Wang
//   2. Lei Chen

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "msgs.h"

#define SERVER_PORT 80

extern Port ports[];
extern TCB_t *RunQ;
extern unsigned int init_buffer_size;

void server(){
    /*create the server table*/
    int i;
    int slot;

    Message table;
    initMsg(&table);

    Message msg;
    initMsg(&msg);

    while(1){
        recv(&ports[SERVER_PORT], &msg);
        unsigned int  found;
        int recv_port = msg.recv_port;
        int req_type = msg.req_type;
        printf("---------------------------------------------------------------\n");
        switch (req_type){
            case REQ_TYPE_GET:
                printf("Server received GET from client %d\n", recv_port);
                table.recv_port = recv_port;
                usleep(1000000);
                send(&ports[recv_port], &table);
                break;
            case REQ_TYPE_ADD:
                printf("Server received ADD from client %d\n", recv_port);
                for (i = 0; i < 10; i++) {
                    if (msg.index[i] != 0) {
                        table.index[i] = 1;
                        if (table.size[i] < msg.size[i]) {
                            table.strs[i] = (char*)realloc(table.strs[i], msg.size[i]);
                            memset(table.strs[i], 0, msg.size[i]);
                            table.size[i] = msg.size[i];
                        }
                        strcpy(table.strs[i], msg.strs[i]);
                    }
                }
                table.recv_port = recv_port;
                for (i = 0; i < 10; i++){
                    if(msg.index[i] != 0)
                        printf("\tSlot %d: %s\n", i, msg.strs[i]);
                }
                usleep(1000000);
                send(&ports[recv_port], &table);
                break;
            case REQ_TYPE_DEL:
                for (i = 0; i < 10; i++) {
                    if (msg.index[i] != 0) {
                        table.index[i] = 0;
                        slot = i;
                    }
                }
                printf("Server received DEL slot %d from client %d\n",slot, recv_port);
                table.recv_port = recv_port;
                usleep(1000000);
                send(&ports[recv_port], &table);
                break;
        }

    }
}



void client(int id){
    char* preStr[10];

    preStr[0] = "pre-defined string 0";
    preStr[1] = "pre-defined string 1";
    preStr[2] = "pre-defined string 2";
    preStr[3] = "pre-defined string 3";
    preStr[4] = "pre-defined string 4";
    preStr[5] = "pre-defined string 5";
    preStr[6] = "pre-defined string 6";
    preStr[7] = "pre-defined string 7";
    preStr[8] = "pre-defined string 8";
    preStr[9] = "pre-defined string 9";

    int i;

    Message msg;
    initMsg(&msg);

    while(1){
        msg.recv_port = id;

        int type = rand() & 1;
        if (type == 1) {
            msg.req_type = REQ_TYPE_ADD;
        } else {
            msg.req_type = REQ_TYPE_DEL;
        }

        for (i = 0; i < 10; i ++) {
            msg.index[i] = 0;
        }

        int index = rand() % 10;
        msg.index[index] = 1;

        int strIndex = rand() % 10;
        int size = strlen(preStr[strIndex]) + 1;

        if (msg.size[index] < size) {
            msg.strs[index] = (char*)realloc(msg.strs[index], size);
            memset(msg.strs[index], 0, size);
        }

        msg.size[index] = size;

        strcpy(msg.strs[index], preStr[strIndex]);
        usleep(1000000);
        printf("---------------------------------------------------------------\n");
        printf("client %d ", id);
        printMsg(msg);
        send(&ports[SERVER_PORT], &msg);
        recv(&ports[id], &msg);// to get the result after sending, currently no use
    }
}

void client3(){
    int i;

    Message msg;
    initMsg(&msg);

    while(1){
        int skip = rand() % 5;
        if (skip != 0) {
            yield();
            continue;
        }
        msg.recv_port = 3;
        msg.req_type = REQ_TYPE_GET;
        usleep(1000000);
        send(&ports[SERVER_PORT], &msg);
        recv(&ports[3], &msg);
        printf("---------------------------------------------------------------\n");
        printf("client 3 ");
        printMsg(msg);
    }
}

void client1() {
    client(1);
}
void client2() {
    client(2);
}

int main(int argc, char** argv){

    printf("******************************************************************\n");
    printf("       CSE 531 Distributed and Multiprocessor OS project #4\n");
    printf("  1. Three clients, one server.\n");
    printf("  2. Server contains a table of 10 slots. Each slot is a string.\n");
    printf("  3. Client 1 and client send request to ADD/DEL slots.\n");
    printf("  4. Client 3 prints out the table, sometimes.\n");
    printf("\n");
    printf("                            team members: Hongxiang Wang, Lei Chen\n");
    printf("******************************************************************\n");
    srand(time(NULL));

    initSems();
    initPorts(ports);
    InitQ(&RunQ);

    start_thread(server);
    start_thread(client1);
    start_thread(client2);
    start_thread(client3);

    run();	
    return 0;
}
