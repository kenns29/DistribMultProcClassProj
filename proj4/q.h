#include "TCB.h"
#include <stdio.h>

#define STACK_SIZE 8192

//Note that if Q is a head pointer to the queue, then InitQ will have to be passed &Q.
void InitQ (TCB_t** head) {
    (*head) = NULL;
} 

void AddQ(TCB_t** head, TCB_t* item) {
    if (NULL == (*head)) {
        (*head) = item;
        item->next = item;
        item->prev = item;
    } else {
        TCB_t* tail = (*head)->prev;
        tail->next = item;
        item->next = (*head);
        (*head)->prev = item;
        item->prev = tail;
    }
}

// will return a pointer to the item deleted.
TCB_t* DelQ(TCB_t** head, int force) {
    if (NULL == head || NULL == (*head))
        return NULL;

    // check if the queue is of size 1
    if ((*head)->next == (*head)) {
        TCB_t* ret = NULL;

        if (force) {
            ret = (*head);
            *head = NULL;
        } 

        return ret;
    }

    TCB_t* ret = (*head);
    TCB_t* tail = (*head)->prev;
    (*head) = (*head)->next;
    (*head)->prev = tail;
    tail->next = (*head);

    return ret;
} 

// deletes the head and adds it to the tail, by just moving the header pointer to the next item.
void RotateQ(TCB_t** head)  {
    if (NULL == head || NULL == (*head))
        return;

    (*head) = (*head)->next;
}

void PrintQ(TCB_t **head) {
    if (NULL == head || NULL == (*head)) {
        printf(" <NULL> \n");
        return;
    }

    TCB_t* cur = *head;
    printf(" <%d> ", (int)cur);
    cur = cur->next;

    while(NULL != cur && cur != (*head)) {
        printf(" [%d] ", (int)(cur));
        cur = cur->next;
    }
    printf("\n");
}

/*void TestQ() {
    TCB_t* head;
    TCB_t* tcb;
    void* stack;

    printf("- - - - - - - - START - - - - - - - - \n");

    InitQ(&head);

    tcb= (TCB_t*)malloc(sizeof(TCB_t));
    stack = malloc(STACK_SIZE);
    init_TCB (tcb, NULL, stack, STACK_SIZE);
    AddQ(&head, tcb);
    printf("\n- - - - - Add [%d] - - - - - - \n", (int)tcb);
    PrintQ(&head);

    printf("\n- - - - - - - - Rotate - - - - - - - - \n");
    RotateQ(&head);
    PrintQ(&head);

    tcb = (TCB_t*)malloc(sizeof(TCB_t));
    stack = malloc(STACK_SIZE);
    init_TCB (tcb, NULL, stack, STACK_SIZE);
    AddQ(&head, tcb);
    printf("\n- - - - - Add [%d] - - - - - - \n", (int)tcb);
    PrintQ(&head);

    printf("\n- - - - - - - - Rotate - - - - - - - - \n");
    RotateQ(&head);
    PrintQ(&head);

    tcb = (TCB_t*)malloc(sizeof(TCB_t));
    stack = malloc(STACK_SIZE);
    init_TCB (tcb, NULL, stack, STACK_SIZE);
    AddQ(&head, tcb);
    printf("\n- - - - - Add [%d] - - - - - - \n", (int)tcb);
    PrintQ(&head);

    printf("\n- - - - - - - - Rotate - - - - - - - - \n");
    RotateQ(&head);
    PrintQ(&head);

    printf("\n- - - - - - - - Rotate - - - - - - - - \n");
    RotateQ(&head);
    PrintQ(&head);

    printf("\n- - - - - - - - Rotate - - - - - - - - \n");
    RotateQ(&head);
    PrintQ(&head);

    printf("\n- - - - - - - - Delete - - - - - - - - \n");
    DelQ(&head, 0);
    PrintQ(&head);

    printf("\n- - - - - - - - Delete - - - - - - - - \n");
    DelQ(&head, 0);
    PrintQ(&head);

    printf("\n- - - - - - - - Delete - - - - - - - - \n");
    DelQ(&head, 0);
    PrintQ(&head);
    }*/



