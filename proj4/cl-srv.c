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

    Message table;
    initMsg(&table);

    Message msg;
    initMsg(&msg);

    while(1){
        printf("################################\n");
        printf("In Server - before receiving msg\n");
        recv(&ports[SERVER_PORT], &msg);
        printf("In Server - Received Message From Client: %d\n", msg.recv_port);
        printMsg(msg);

        int recv_port = msg.recv_port;
        int req_type = msg.req_type;
        switch (req_type){
            case REQ_TYPE_GET:
                table.recv_port = recv_port;
                printf("Sending Message to Client:\n");
                printMsg(table);
                usleep(1000000);
                send(&ports[recv_port], table);
                break;
            case REQ_TYPE_ADD:
                for (i = 0; i < 10; i++) {
                    if (msg.index[i] != 0) {
                        if (table.size[i] < msg.size[i]) {
                            table.strs[i] = (char*)realloc(table.strs[i], msg.size[i]);
                        }
                        strcpy(table.strs[i], msg.strs[i]);
                    }
                }
                table.recv_port = recv_port;
                printf("Sending Message to Client:\n");
                printMsg(table);
                usleep(1000000);
                send(&ports[recv_port], table);
                break;
            case REQ_TYPE_DEL:
                for (i = 0; i < 10; i++) {
                    if (msg.index[i] != 0) {
                        table.index[i] = 0;
                    }
                }
                table.recv_port = recv_port;
                printf("Sending Message to Client:\n");
                printMsg(table);
                usleep(1000000);
                send(&ports[recv_port], table);
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
        printf("################################\n");
        printf("In Client %d\n", id);
        msg.recv_port = id;

        int type = 1;//rand() & 1;
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
        msg.size[index] = size;

        strcpy(msg.strs[index], preStr[strIndex]);

        printf("Sending Message to Server:\n");
        printMsg(msg);
        usleep(1000000);
        send(&ports[SERVER_PORT], msg);
        recv(&ports[id], &msg);
    }
}

void client3(){
    int i;

    Message msg;
    initMsg(&msg);

    while(1){
        printf("################################\n");
        printf("In Client 3\n");
        printf("Sending Message to Server:\n");
        msg.recv_port = 3;
        msg.req_type = REQ_TYPE_GET;
        printMsg(msg);
        usleep(1000000);
        send(&ports[SERVER_PORT], msg);
        recv(&ports[3], &msg);
        printf("Received Message:\n");
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
