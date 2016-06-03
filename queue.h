#ifndef _QUEUE_
#define _QUEUE_
struct node{
    int value;
    struct node *next;
};

struct queue{
    int size;
    struct node * head;
    struct node * tail;
};

// queue library
void init_q(struct queue *q);
void add_q(struct queue *q, int v);
int empty_q(struct queue *q);
int pop_q(struct queue *q);
int front(struct queue *q);



#endif
