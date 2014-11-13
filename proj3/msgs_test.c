#include "msgs.h"
#include <stdio.h>
#include <stdlib.h>

/*void sent(Port port, Message msg){

  printf("HERE\n");
  printMsg(msg);
  printf("port->in = %d\n", port.in);

  Sem_t* mutex = getMutex(port);
  Sem_t* fullSem = getFullSem(port);
  Sem_t* emptySem = getEmptySem(port);

  P(fullSem);
  P(mutex);

  copyMsg(msg, &port.msgs[port.in]);

  printMsg(port.msgs[port.in]);
  port.in = (port.in + 1) % MSG_SIZE;
  usleep(1000000);

  V(mutex);
  V(emptySem);

}*/

int main(int argc, char **argv){

  //extern Port ports[];
  
  
  
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
