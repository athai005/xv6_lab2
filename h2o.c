#include "semaphore.c"
#include "types.h"
#include "user.h"

struct thread{
	int tid;
	int holding;
};

struct{
	lock_t lock;
	struct thread thread[64];
	int total;
}ttable;

struct Semaphore h,o,l;
int water = 0;

void watermade()
{
	printf(1, "water made");
	return;
}
void hReady(void* v)
{
   sem_signal(&h);
   sem_acquire(&o);
}

void oReady(void* v)
{
   sem_acquire(&h);
   sem_acquire(&h);
   sem_signal(&o);
   sem_signal(&o);
   sem_acquire(&l);
   water++;
   watermade();
   //printf(0,"water created\n");
   sem_signal(&l);
}

int main()
{
   sem_init(&h, 0);
   sem_init(&o, 0);
   sem_init(&l, 1);

   void *tid1 = thread_create(hReady, (void*)0);
   if (tid1 == 0) printf(1, "thread_create failed\n");
   void *tid2 = thread_create(hReady, (void*)0);  
   if (tid2 == 0) printf(1, "thread_create failed\n");
   void *tid3 = thread_create(oReady, (void*)0);
   if (tid3 == 0) printf(1, "thread_create failed\n");

   return 0;
}

