#include "sem.h"
#define MSG_SIZE  10
#define PORT_SIZE  100

#define SEM_CASE = 2; //2 ,3 

#define REQ_TYPE_GET 0
// get the whole table
// int count;
//      int index;
//      char* str; 

#define REQ_TYPE_ADD 1
// add one string to the table
// int index;
//      char* str;

#define REQ_TYPE_MOD 2
// modify one string in the table
// int index;
//      char* str;

#define REQ_TYPE_DEL 3
// delete one string in the table
// int index;


/*Message structure that contains the pseudo protocol*/
typedef struct MSG{
    int recv_port;
    int req_type;
    void* req_data;
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
    switch(msg->req_type) {
        case REQ_TYPE_GET:
            // int count;
            //      int index;
            //      int size;
            //      char* str; 

            void* cur = msg->req_data;
            int count = *((int*)cur);
            cur += sizeof(int);
            printf("REQ_GET: count = %d\n", count);
        
            for (int i = 0; i < count; i++) {
                int index = *((int*)cur);
                cur += sizeof(int);
                int size =  *((int*)cur);
                cur += sizeof(int);
                printf("%d:%s\n", i, cur);
                cur += sizeof(char) * size;
            }
                
            break;
        case REQ_TYPE_ADD:
            // int index;
            //      int size;
            //      char* str;
            break;
        case REQ_TYPE_MOD:
            // int index;
            //      int size;
            //      char* str;
            break;
        case REQ_TYPE_DEL:
            // int index;
            break;
        default:
    }
}

void initMsg(Message *msg){
    msg->size = init_buffer_size;
    msg->msg = (char*)malloc(msg->size*sizeof(char));
    strcpy(msg->msg, "\0");
    msg->recv_port = 0;
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
    to->size = from.size;
    to->recv_port = from.recv_port;
    strcpy(to->msg, from.msg);
    to->request_type = from.request_type;
    to->message_index = from.message_index;
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
    yield();
}

void recv(Port *port, Message *msg){

    Sem_t *mutex = getMutex(*port);
    Sem_t *fullSem = getFullSem(*port);
    Sem_t *emptySem = getEmptySem(*port);

    P(emptySem);
    P(mutex);
    copyMsg(port->msgs[port->out], msg);
    port->out = (port->out + 1) % MSG_SIZE;

    V(mutex);
    V(fullSem);
    yield();
}




