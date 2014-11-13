#include "sem.h"
#define MSG_SIZE  10
#define PORT_SIZE  100


const int CASE = 1; //2 ,3 

typedef struct MSG{
	int msg[10];
}Message;

typedef struct{
	int number;
	Message msgs[MSG_SIZE];
	int in;
	int out;
}Port;


Port ports[PORT_SIZE];

Sem_t *mutexes[PORT_SIZE];
Sem_t *fullSems[PORT_SIZE];
Sem_t *emptySems[PORT_SIZE];

Sem_t* getMutex(Port port) {
	int index = 0;
	switch (CASE) {
		case 2:
			index = port.number;
			break;	

		case 3:
			index = port.number/10;
			break;
	}

	return mutexes[index];
}

Sem_t* getFullSem(Port port) {
	int index = 0;
	switch (CASE) {
		case 3:
			index = port.number/10;
			break;
		case 1:
		case 2:
		default:
			index = port.number;
	}

	return fullSems[index];
}

Sem_t* getEmptySem(Port port) {
	int index = 0;
	switch (CASE) {
		case 3:
			index = port.number/10;
			break;
		case 1:
		case 2:
		default:
			index = port.number;
	}

	return emptySems[index];
}

void printMsg(Message msg){
  int i ;
  for(i = 0; i < 10; i++){
    printf("%d ", msg.msg[i]);
  }
  printf("\n");
}


void initMsg(Message *msg){
  int i;
  for(i = 0; i < 10; i++){
    msg->msg[i] = 0;
  }
}

void initPorts(Port ports[]){
  int i;
  
  for(i = 0; i < PORT_SIZE; i ++){
    ports[i].in = 0;
    ports[i].out = 0;
    ports[i].number = i;
    int j;
    
    for(j = 0; j < MSG_SIZE; j++){
      initMsg(&ports[i].msgs[j]);
    }
  }
}

void initSems(){
	int i;
	
	for(i=0; i < PORT_SIZE; i++){
		mutexes[i] = CreateSem(1);
		emptySems[i] = CreateSem(0);
		fullSems[i] = CreateSem(MSG_SIZE);
	}
       
}

void copyMsg(Message from, Message *to){
  int i;
  for(i = 0; i < MSG_SIZE; i++){
    to->msg[i] = from.msg[i];
  }
}

void send(Port *port, Message msg){
	Sem_t* mutex = getMutex(*port);
	Sem_t* fullSem = getFullSem(*port);
	Sem_t* emptySem = getEmptySem(*port);
      
	P(fullSem);
	P(mutex);
       
	copyMsg(msg, &port->msgs[port->in]);
	port->in = (port->in + 1) % MSG_SIZE;

	V(mutex);
	V(emptySem);

}

void recv(Port port, Message *msg){
  
  Sem_t *mutex = getMutex(port);
  Sem_t *fullSem = getFullSem(port);
  Sem_t *emptySem = getEmptySem(port);

  P(emptySem);
  P(mutex);
  copyMsg(port.msgs[port.out], msg);
  port.out = (port.out + 1) % MSG_SIZE;

  V(mutex);
  V(fullSem);
  
}




