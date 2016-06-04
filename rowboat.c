#include "semaphore.c"
#include "thread.h"


Semaphore l;
Semaphore m;
Semaphore c;

int miss = 0;
int cann = 0;

int numm = 0;
int numc = 0;

void rowboat()
{
   printf(1,"Rowboat sent\n");
}

void MissionaryArrives(void* v)
{
   sem_acquire(&l);
   miss++;
   if(miss+cann<3 || (miss == 1 && cann == 2))
   {
      sem_signal(&l);
      sem_acquire(&m);
     // sem_acquire(&l);
   }
   else
   {
      if (miss >= 3)
      {
         miss = miss - 3;
         sem_signal(&m);
         sem_signal(&m);
   			 sem_signal(&l);
   			 rowboat();
   			 
				printf(1, "Boat left with 3 Missionaries\n");
      }
      else if(miss >= 2 && cann >= 1)
      {
         miss = miss-2;
         cann--;
         sem_signal(&c);
         sem_signal(&l);
   			 rowboat();
				printf(1, "Boat left with 2 Missionaries, 1 cannibal\n");
      }
      else if (miss == 1 && cann == 2) 
      {
      	sem_signal(&l);
      	exit();
      }
   }
   texit();
}

void CannibalArrives(void* v)
{
   sem_acquire(&l);
   cann++;
   if(miss+cann<3 || (miss==1 && cann==2))
   {
      sem_signal(&l);
      sem_acquire(&c);
   }
   else
   {
      if (cann >= 3) 
      {
         cann = cann -3;
         sem_signal(&c);
         sem_signal(&c);
         sem_signal(&l);
         rowboat();
				printf(1, "Boat left with 3 Missionaries\n");
      }
      else if(miss>=2 && cann >= 1)
      {
         miss=miss-2;   
         cann--;
         sem_signal(&m);
         sem_signal(&m);
         sem_signal(&l);
         rowboat();
				printf(1, "Boat left with 2 Missionaries, 1 cannibal\n");
      }
      else if (miss == 1 && cann == 2) 
      {
      	sem_signal(&l);
      	exit();
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
	/*
	if ( (numm + numc)%3 != 0)
	{
		numm = numm - (numm%3);
		numc = numc - (numc%3);
	}
	*/
	//else if (numm%3 == 1 && numc%3 == 2) exit();

   Sem_init(&l, 1);
   Sem_init(&m, 0);
   Sem_init(&c, 0);

	int i = 0;
	for (i = 0; i < numm; i++)
	{
		thread_create(MissionaryArrives, (void*)0);
	}
	for (i = 0; i < numc; i ++)
	{
		thread_create(CannibalArrives, (void*)0);
	}

	while(wait() >= 0);

   exit();

}
