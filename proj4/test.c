#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define REQ_TYPE_GET 0
#define REQ_TYPE_ADD 1
#define REQ_TYPE_DEL 2

typedef struct {
    int count;
    int* index;
    int* size;
    char** str;
} RequestData;


typedef struct MSG{
    int recv_port;
    int req_type;
    RequestData req_data;
}Message;

void printMsg(Message msg){
    int i;
    switch(msg.req_type) {
        case REQ_TYPE_GET:
            printf("REQ_GET:\n");
            break;
        case REQ_TYPE_MOD:
            printf("REQ_ADD:\n");
            break;
        case REQ_TYPE_DEL:
            printf("REQ_DEL:\n");
            break;
        default:
            break;
    }
    RequestData data = msg.req_data;
    for (i = 0; i < data.count; i++) {
        printf("    %d: %.*s\n", i, *(data.size + i), *(data.str + i));
    }
}

int main(int argc, char** argv){
    Message msg;
    msg.recv_port = 1;
    msg.req_type = REQ_TYPE_GET;
    msg.req_data.count = 2;

    msg.req_data.index = (int*)malloc(sizeof(int)*2);
    *(msg.req_data.index) = 0;
    *(msg.req_data.index+1) = 1;

    msg.req_data.size = (int*)malloc(sizeof(int)*2);
    *(msg.req_data.size) = 5;
    *(msg.req_data.size+1) = 10;


    msg.req_data.str = (char**)malloc(sizeof(char*)*2);
    *(msg.req_data.str) = (char*)malloc(sizeof(char)*5);
    *(msg.req_data.str+1) = (char*)malloc(sizeof(char)*10);

    strcpy(*(msg.req_data.str), "abcd");
    strcpy(*(msg.req_data.str+1), "123456789");

    printMsg(msg);

    return 0;
}
