#ifndef _SEMAPHORE_
#define _SEMAPHORE_
#include "queue.c"
struct Semaphore
{
   int count;
   struct queue q;
};

void sem_init(struct Semaphore * s, int v)
{
   s->count = v;
   init_q(&(s->q)); 
}

void sem_acquire(struct Semaphore *s)
{
   //if count is positive, decrement count
   if(s->count > 0)
   {
      (s->count)--;
   }
   //if count is zero, thread added to queue and waits
   else
   {
      add_q(&(s->q),getpid());
      while(s->count == 0 || front(&(s->q)) != getpid()) wait();
   }
}

void sem_signal(struct Semaphore *s)
{
   //increment count
   (s->count)++;
}
#endif
