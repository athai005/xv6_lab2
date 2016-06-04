#include "semaphore.c"
#include "thread.h"


Semaphore l;
Semaphore m;
Semaphore c;

int miss = 0;
int cann = 0;

int numm = 0;
int numc = 0;

int numthreads = 0;
int threadcount = 0;

void rowboat()
{
   printf(1,"Rowboat sent; Passengers are ");
}

void MissionaryArrives(void* v)
{
   sem_acquire(&l);
   miss++;
   if(miss+cann<3 && threadcount < numthreads)
   {
      sem_signal(&l);
      sem_acquire(&m);
     // sem_acquire(&l);
   }
   else
   {
      if (miss == 1 && cann == 2) 
      {
      	sem_signal(&l);
      	texit();
      }
      else if (miss >= 3)
      {
         miss = miss - 3;
         sem_signal(&m);
         sem_signal(&m);
   			 sem_signal(&l);
   			 rowboat();
   			 
				printf(1, "3 Missionaries\n");
      }
      else if(miss >= 2 && cann >= 1)
      {
         miss = miss-2;
         cann--;
         sem_signal(&c);
         sem_signal(&l);
   			 rowboat();
				printf(1, "2 Missionaries, 1 cannibal\n");
      }
      else
      {
      	sem_signal(&l);
      	texit();
      }
   }
   texit();
}

void CannibalArrives(void* v)
{
   sem_acquire(&l);
   cann++;
   if(miss+cann<3 && threadcount < numthreads)
   {
      sem_signal(&l);
      sem_acquire(&c);
   }
   else
   {
      if (miss == 1 && cann == 2) 
      {
      	sem_signal(&l);
      	texit();
      }
      else if (cann >= 3) 
      {
         cann = cann -3;
         sem_signal(&c);
         sem_signal(&c);
         sem_signal(&l);
         rowboat();
				printf(1, "3 Cannibals\n");
      }
      else if(miss>=2 && cann >= 1)
      {
         miss=miss-2;   
         cann--;
         sem_signal(&m);
         sem_signal(&m);
         sem_signal(&l);
         rowboat();
				printf(1, "2 Missionaries, 1 cannibal\n");
      }
      else
      {
      	sem_signal(&l);
      	texit();
      }
   }
   texit();
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf(1, "Proper use: rowboat <#Missionaries> <#Cannibals>\n");
		exit();
	}

	numm = atoi(argv[1]);
	numc = atoi(argv[2]);

	if (numm == 1 && numc == 2)
	{
		printf(1, "Congratulations! You just let two cannibals kill a missionary.\n");
		exit();
	}
	if (numm + numc < 3)
	{
		exit();
	}
	if ( numm%3 == 1 && numc%3 == 2)
	{
		numm = numm - (numm%3);
		numc = numc - (numc%3);
	}
	//else if (numm%3 == 1 && numc%3 == 2) exit();

   Sem_init(&l, 1);
   Sem_init(&m, 0);
   Sem_init(&c, 0);

	int i = 0;
  numthreads = numm + numc;	
  threadcount = 0;
	void * slist[numthreads];
	for(i=0; i < numthreads; i++)	
	{
		slist[i] = 0;
	}

	for (i = 0; i < numm; i++)
	{
		void * tidm = thread_create(MissionaryArrives, (void*)0);
		slist[threadcount] = tidm;
		threadcount++;
	}
	for (i = 0; i < numc; i ++)
	{
		void * tidc = thread_create(CannibalArrives, (void*)0);
		slist[threadcount] = tidc;
		threadcount++;
	}

	while(wait() >= 0) 
	{
		if ((miss == 1 && cann == 2)) break;
		if ((miss + cann)%3 != 0 && threadcount != numthreads) break;
	}

	for (i = 0; i < numthreads ; i++)
	{
		if (slist[i] != 0)
		{
			void * f = slist[i];
			free(f); 
	  }
	}

   exit();

}
