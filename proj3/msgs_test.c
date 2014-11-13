#include "msgs.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){
  extern Port ports[];
  
  initSems();
  
  initPorts(ports);

  Message sendMsg;
  Message recvMsg;
  
  int i;
 
  for(i =0; i < 10; i++){
    sendMsg.msg[i] = i;
  }

  printMsg(ports[0].msgs[0]);
  send(&ports[0], sendMsg);
  
  recv(ports[0], &recvMsg);
   
  for(i =0; i < 10; i++){
    printf("%d\n", recvMsg.msg[i]);
  }
  return 0;
}
