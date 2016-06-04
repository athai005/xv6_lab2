#include "semaphore.c"
#include "thread.h"

void hReady(void*);
void oReady(void*);

int water = 0;
int numh = 0;
int numo = 0;

Semaphore h;
Semaphore o;
Semaphore l;


int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		printf(1, "Proper use: h2o_custom <#hydrogen> <#oxygen> \n");
		exit();
	} 

	numh = atoi(argv[1]);
	numo = atoi(argv[2]);

  Sem_init(&h, 0);
  Sem_init(&o, 0);
  Sem_init(&l, 1);

  int i = 0;

	for(i = 0; i < numh; i++)
	{
		thread_create(hReady,(void*)&water);
	}
	for(i = 0; i < numo; i++)
	{
		thread_create(oReady,(void*)&water);
	}
   
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
   printf(1,"water molecule #%d created\n", water);
   sem_signal(&l);

   texit();
}
