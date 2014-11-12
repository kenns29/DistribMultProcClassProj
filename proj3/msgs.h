#include "sem.h"


const int CASE = 1; //2 ,3 
const int MSG_SIZE = 10;
const int PORT_SIZE = 100;

typedef struct MSG{
	int msg[10];
}Message;

typedef struct{
	int number;
	Message* msgs[MSG_SIZE];
	int in;
	int out;
}Port;


Port ports[PORT_SIZE];

Sem_t *mutexes[PORT_SIZE];
Sem_t *fullSems[PORT_SIZE];
Sem_t *emptySems[PORT_SIZE];

void initSems(Sem_t **fullSems, Sem_t **emptySems, Sem_t **mutexes){
	int i;
	for(i=0; i < PORT_SIZE; i++){
		mutexes[i] = CreateSem(1);
		emptySems[i] = CreateSem(0);
		fullSems[i] = CreateSem(MSG_SIZE);
	}
}

void sent(Port* port, Message *msg){
	if (NULL == port || NULL == msg) {
		return;
	}

	Sem_t* mutex = getMutex(port);
	Sem_t* fullSem = getFullSem(port);
	Sem_t* emptySem = getEmptySem(port);

	P(fullSem);
	P(mutex);

	port->msgs[port->in] = msg;
	in = (in + 1) % MSG_SIZE;
	usleep(1000000);

	V(mutex);
	V(empty);

	yield();
}

void recv(Port*port, Message *msg){

}

Sem_t* getMutex(Port* port) {
	int index = 0;
	switch (CASE) {
		case 2:
			index = port->number;
			break;	

		case 3:
			index = port->number/10;
			break;
		case 1:
		default:
	}

	return mutexes[index];
}

Sem_t* getFullSem(Port* port) {
	int index = 0;
	switch (CASE) {
		case 3:
			index = port->number/10;
			break;
		case 1:
		case 2:
		default:
			index = port->number;
	}

	return fullSems[index];
}

Sem_t* getEmptySem(Port* port) {
	int index = 0;
	switch (CASE) {
		case 3:
			index = port->number/10;
			break;
		case 1:
		case 2:
		default:
			index = port->number;
	}

	return emptySems[index];
}
