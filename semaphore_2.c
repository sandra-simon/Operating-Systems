#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int semaphore=1,state=1;
void wait(int *semaphore)			//int *variable is the pointer to an int value,ie.address of that int value in mem
{
	while(*semaphore <= 0);
	*semaphore--;
}

void signal(int *semaphore)
{
	sleep(1);
	*semaphore++;
}

int arr[20],bufsize=20,in=0,out=0;
void insert(int itemp)
{
	if((in+1)%bufsize == out)
	{
		printf("Buffer is full.\n");
	}
	else
	{
		arr[in]=itemp;
		in=(in+1)%bufsize;
	}
}
int consumed;
void deletefrom()
{
	if(in != out)
	{
		consumed=arr[out];
                out=(out+1)%bufsize;
	}
	else
	{
		printf("Buffer is empty.\n");
	}
}

void *f1(void *arg)
{
	int itemp=*((int*)arg);
	while(1)
	{
		if(state==itemp)
		{
			wait(&semaphore);
			printf("Produced : %d\n",itemp);
			insert(itemp);
			sleep(1);
			itemp++;
			state++;
			signal(&semaphore);
		}
	}
	pthread_exit(NULL);
}

void *f2()
{
	while(1)
	{
		wait(&semaphore);
		sleep(1);
		deletefrom();
		int itemc=consumed;
		printf("Consumed : %d\n",itemc);
		signal(&semaphore);
	}
	pthread_exit(NULL);
}

void main()
{
	int item=1;
	pthread_t t1,t2;
	pthread_create(&t1,NULL,f1,&item);
	pthread_create(&t2,NULL,f2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
