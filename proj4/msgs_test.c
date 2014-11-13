#include "msgs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SERVER_PORT 80
extern Port ports[];
extern TCB_t *RunQ;

void server();
void client(int);

void client1();
void client2();
void client3();

int main(int argc, char **argv){


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

void server(){
    Message msg;
    while(1){
        recv(&ports[SERVER_PORT], &msg);
        int client_port = msg.msg[0];
        printf("##################\n");
        printf("\tIn Server\n");
        printf("\tReceived Message from Client %d. Message:\n\t", client_port);
        printMsg(msg);
        srand(time(NULL));
        int i;
        for(i=1; i<10;i++){
            msg.msg[i] = rand() % 10;
        }

        printf("\tSending Message to Client %d. Message:\n\t", client_port);
        printMsg(msg);
        send(&ports[client_port], msg);

        //yield();
    }
}

void client(int client_no/*cannot be 80*/){
    int port_no = client_no;
    Message send_msg;
    Message recv_msg;
    send_msg.msg[0] = port_no;
    int i;
    srand(time(NULL));
    for(i = 1; i< 10; i++){
        send_msg.msg[i] = rand() % 10; 
    }
    printf("##################\n");
    printf("\tIn Client %d\n", client_no);
    printf("\tSending Message to Server. Message:\n\t");
    printMsg(send_msg);
    send(&ports[SERVER_PORT], send_msg);
    recv(&ports[port_no], &recv_msg);
    printf("##################\n");
    printf("\tIn Client %d\n", client_no);
    printf("\tReceived Message from Server. Message:\n\t");
    printMsg(recv_msg);  
}

void client1(){
    while(1){
        client(1);
        usleep(1000000);
        //yield();
    }
}
void client2(){
    while(1){
        client(2);
        usleep(1000000);
        //yield();
    }
}
void client3(){
    while(1){
        client(3);
        usleep(1000000);
        //yield();
    }
}
