#include "sem.h"


const int MSG_SIZE = 10;
const int PORT_NUM = 100;
typedef struct MSG{
  int msg[10];
}Message;

typedef struct{
  Message msgs[MSG_SIZE];
}Port;

Sem_t *mutex = CreateSem(1);

Port ports[PORT_NUM];

Sem_t *full[PORT_NUM];
Sem_t *empty[PORT_NUM];

void initSems(Sem_t **full, Sem_t **empty){
  int i;
  for(i=0; i < PORT_NUM; i++){
    
  }
}
void sent(Port* port, Message *msg){
  
}

void recv(Port*port, Message *msg){

}
