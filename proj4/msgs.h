#include "sem.h"
#define MSG_SIZE  10
#define PORT_SIZE  100

#define SEM_CASE 2 //2 ,3 

#define REQ_TYPE_GET 0
#define REQ_TYPE_ADD 1
#define REQ_TYPE_MOD 2
#define REQ_TYPE_DEL 3

#define DEFAULT_STR_SIZE 10

/*Message structure that contains the pseudo protocol*/
typedef struct MSG{
    int recv_port;
    int req_type;
    int index[10];// 0 = empty, !0 = not empty
    int size[10];
    char* strs[10];
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
    switch (SEM_CASE) {
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
    switch (SEM_CASE) {
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
    switch (SEM_CASE) {
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
    int i;
    int recv_port;
    int req_type;
    int index[10];
    char* strs[10];
    switch(msg.req_type) {
        case REQ_TYPE_GET:
            printf("GET\n");
            for (i = 0; i < 10; i++) {
                if (msg.index[i] != 0) {
                    printf("\tslot %d: %s\n", i, msg.strs[i]);
                }
            }
            break;
        case REQ_TYPE_ADD:
            printf("ADD\n");
            for (i = 0; i < 10; i++) {
                if (msg.index[i] != 0) {
                    printf("\tslot %d: %s\n", i, msg.strs[i]);
                }
            }
            break;
        case REQ_TYPE_DEL:
            printf("DEL\n");
            for (i = 0; i < 10; i++) {
                if (msg.index[i] != 0) {
                    printf("\tslot %d\n", i);
                }
            }
            break;
    }
    //printf(", port = %d\n", msg.recv_port);
    //printf("Index: ");
    //for	(i = 0; i < 10; i++){
    //	printf("%d  ", msg.index[i]);
    //}
    //printf("\n");
    //printf("size : ");
    //for	(i = 0; i < 10; i++){
    //	printf("%d ", msg.size[i]);
    //}
}

void initMsg(Message *msg){
    int i;
    msg->recv_port = -1;
    msg->req_type = REQ_TYPE_GET;
    for (i = 0; i < 10; i++) {
        msg->index[i] = 0;// 0 = empty, !0 = not empty
        msg->size[i] = DEFAULT_STR_SIZE;
        msg->strs[i] = (char*)calloc(DEFAULT_STR_SIZE, sizeof(char));
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

void copyMsg(Message *from, Message *to){
    int i;
    to->recv_port = from->recv_port;
    to->req_type = from->req_type;
    for (i = 0; i < 10; i++) {
        to->index[i] = from->index[i];
        if (from->size[i] > to->size[i]) {
            //to->strs[i] = (char*)realloc(to->strs[i], from->size[i]);
            free(to->strs[i]);
            to->strs[i] = (char*)calloc(from->size[i], sizeof(char));
            to->size[i] = from->size[i];
        } 
        strcpy(to->strs[i], from->strs[i]);
    }
}

void send(Port *port, Message *msg){
    Sem_t* mutex = getMutex(*port);
    Sem_t* fullSem = getFullSem(*port);
    Sem_t* emptySem = getEmptySem(*port);

    P(fullSem);
    P(mutex);

    copyMsg(msg, &port->msgs[port->in]);
    port->in = (port->in + 1) % MSG_SIZE;

    V(mutex);
    V(emptySem);
    yield();
}

void recv(Port *port, Message *msg){

    Sem_t *mutex = getMutex(*port);
    Sem_t *fullSem = getFullSem(*port);
    Sem_t *emptySem = getEmptySem(*port);

    P(emptySem);
    P(mutex);
    copyMsg(&(port->msgs[port->out]), msg);

    port->out = (port->out + 1) % MSG_SIZE;

    V(mutex);
    V(fullSem);
    yield();
}
