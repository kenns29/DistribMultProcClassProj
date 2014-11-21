#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "msgs.h"
#define SERVER_PORT 80
#define REQ_PRINT 0
#define REQ_PRINT_ALL 1
#define REQ_MOD 2
#define REQ_DEL 3
#define MSG_TABLE_SIZE 10

extern Port ports[];
extern TCB_t *RunQ;
extern init_buffer_size;

void server();
void client();
int main(int argc, char** argv){
  srand(time(NULL));
  return 0;
}


void server(){
  Message msg;
  while(1){
    recv(&ports[SERVER_PORT], &msg);
    int client_port = msg.recv_port;
    
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
  case REQ_PRINT:
    send_msg.message_index = rand() % MSG_TABLE_SIZE;
    send_msg.recv_port = client_no;
    send_msg.msg = (char*)calloc(init_buffer_size, sizeof(char));
    send(&ports[SERVER_PORT], send_msg);
    recv(&ports[send_msg.recv_port], &recv_msg);
    
    break;
  case REQ_MOD:
    
    break;
  case REQ_DEL:
    break;
  }
}
