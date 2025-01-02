#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define n 4
#define NIL 127
char arr[n];
int mutex=1,E=n,F=0;
void wait(int *S)
{
        while((*S)==0)
                ;
        (*S)--;
}
void signal(int *S)
{
        (*S)++;
}
void initialize()
{
        int i;
        for(i=0;i<n;i++)
        {
                arr[i]=NIL;
        }
}
void display()
{
        int i;
        for(i=0;i<n;i++)
        {
                if(arr[i]==NIL)
                {
                        printf("_ ");
                }
                else if(arr[i]>90)
                {
                        printf("%c ",arr[i]);
                }
                else
                {
                        printf("%d ",arr[i]);
                }
        }
        printf("\n\n");
}
void* producer1(void* arg)
{
        int num=0;
        while(1)
        {
                wait(&E);
                wait(&mutex);
                sleep(3);
                for(int i=0;i<n;i++)
                {
                        if(arr[i]==NIL)
                        {
                                arr[i]=num;
                                break;
                        }
                }
                printf("PUT_P1 : %d Buffer : ",num++);
                display();
                signal(&mutex);
                signal(&F);
        }
        pthread_exit(NULL);
}
void* producer2(void* arg)
{
        int ch='a';
        while(1)
        {
                int num=rand()%100;
                wait(&E);
                wait(&mutex);
                sleep(3);
                for(int i=0;i<n;i++)
                {
                        if(arr[i]==NIL)
                        {
                                arr[i]=ch;
                                break;
                        }
                }
                printf("PUT_P2 : %c Buffer : ",ch++);
                display();
                signal(&mutex);
                signal(&F);
        }
        pthread_exit(NULL);
}
void* consumer(void* arg)
{
        while(1)
        {
                int num;
                wait(&F);
                wait(&mutex);
                sleep(1);
                for(int i=0;i<n;i++)
                {
                        if(arr[i]!=NIL)
                        {
                                num=arr[i];
                                arr[i]=NIL;
                                break;
                        }
                }
                if(num>90)
                {
                        printf("GET : %c Buffer : ",num);
                }
                else
                {
                        printf("GET : %d Buffer : ",num);
                }
                display();
                signal(&mutex);
                signal(&E);
        }
        pthread_exit(NULL);
}
void main()
{
        pthread_t p1,p2,c;
        pthread_attr_t attr;
        initialize();
        pthread_attr_init(&attr);
        pthread_create(&p1,&attr,producer1,NULL);
        pthread_create(&p2,&attr,producer2,NULL);
        pthread_create(&c,&attr,consumer,NULL);
        pthread_join(p1,NULL);
        pthread_join(p2,NULL);
        pthread_join(c,NULL);
}
