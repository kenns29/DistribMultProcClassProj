#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "msgs.h"

#define SERVER_PORT 80

extern Port ports[];
extern TCB_t *RunQ;
extern unsigned int init_buffer_size;

void server();
void client1();
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


void server(){
    /*create the server table*/
    int i;

    int index[10];// 0 = empty, !0 = not empty
    int size[10];
    char *strs[10];
    for (i = 0; i < 10; i++) {
        msg->index[i] = 0;
        msg->size[i] = DEFAULT_STR_SIZE;
        msg->strs[i] = (char*)calloc(DEFAULT_STR_SIZE, sizeof(char));
    }

    Message msg;
    initMsg(&msg);

    while(1){
        recv(&ports[SERVER_PORT], &msg);
        int client_port = msg.recv_port;
        int request_type = msg.req_type;
        switch (request_type){
            case REQ_PRINT:
                if(strlen(server_table[req_index]) == 0){
                    strcpy(msg.msg, "Item ");
                    char *temp = (char*)malloc(10*sizeof(10));
                    sprintf(temp, "%d", req_index);
                    strcat(msg.msg, temp);
                    strcat(msg.msg, " in Server Table is empty");
                    free(temp);
                }
                else{
                    strcpy(msg.msg, server_table[req_index]);
                }
                send(&ports[client_port], msg);
                break;
            case REQ_PRINT_ALL:
                break;
            case REQ_MOD:
                strcpy(server_table[req_index], msg);
                strcpy(msg.msg, "SUCCESS");
                send(&ports[client_port], msg);
                break;
            case REQ_DEL:
                server_table[req_index][0] = '\0';
                strcpy(msg.msg, "SUCCESS");
                send(&ports[client_port], msg);
                break;
        }

    }
}

/*request type*/
/*0->print, 1->printAll, 2->modify, 3->delete*/
void client1(){
    int client_no = 1;
    Message send_msg;
    Message recv_msg;
    const char *client_str[3];
    client_str[0] = "client 1 str 1";
    client_str[1] = "client 1 str 2";
    client_str[2] = "client 1 str 3";
    int request_type;
    do{
        request_type = rand() % REQ_NUM;
    }while(request_type == REQ_PRINT_ALL);

    switch (request_type){
        case REQ_MOD:
            send_msg.message_index = rand() % SERVER_TABLE_SIZE;
            send_msg.recv_port = client_no;
            send_msg.msg = (char*)malloc(init_buffer_size* sizeof(char));
            strcpy(send_msg.msg, client_str[rand()%3]); 
            send_msg.size = init_buffer_size;
            send(&ports[SERVER_PORT], send_msg);
            recv(&ports[send_msg.recv_port], &recv_msg);
            free(send_msg.msg);
            break;
        case REQ_PRINT:
            send_msg.message_index = rand() % SERVER_TABLE_SIZE;
            send_msg.recv_port = client_no;
            send_msg.msg = (char*)calloc(init_buffer_size, sizeof(char));
            send_msg.size = init_buffer_size;
            send(&ports[SERVER_PORT], send_msg);
            recv(&ports[send_msg.recv_port], &recv_msg);
            printMsg(recv_msg);
            free(send_msg.msg);
            break;
        case REQ_DEL:
            send_msg.message_index = rand() % SERVER_TABLE_SIZE;
            send_msg.recv_port = client_no;
            send_msg.msg = (char*)calloc(init_buffer_size, sizeof(char));
            send_msg.size = init_buffer_size;
            send(&ports[SERVER_PORT], send_msg);
            recv(&ports[send_msg.recv_port], &recv_msg);
            free(send_msg.msg);
            break;
    }

}


