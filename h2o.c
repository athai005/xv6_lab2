#include "semaphore.c"
#include "thread.h"

void hReady(void*);
void oReady(void*);

int water = 0;

Semaphore h;
Semaphore o;
Semaphore l;

int main()
{
	printf(1, "Combining 2 hydrogen and 1 oxygen\n");
	printf(1, "1 water molecule should be created\n\n");

   Sem_init(&h, 0);
   Sem_init(&o, 0);
   Sem_init(&l, 1);


   thread_create(hReady,(void*)&water);
   thread_create(hReady,(void*)&water);  
   thread_create(oReady,(void*)&water);
   
   //main waits for threads to exit   
   while(wait() >= 0);

   exit();
}

void hReady(void* v)
{
   sem_signal(&h);
   sem_acquire(&o);
   texit();
}

void oReady(void* v)
{
   sem_acquire(&h);
   sem_acquire(&h);
   sem_signal(&o);
   sem_signal(&o);
   sem_acquire(&l);
   water++;
   printf(1,"water molecule created\n");
   sem_signal(&l);

   texit();
}
