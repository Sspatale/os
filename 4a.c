#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#define buffersize 10
pthread_mutex_t m;
pthread_t tidP[10],tidC[10];
sem_t full,empty;
int counter,item;
int buffer[buffersize];
void initialize() {
pthread_mutex_init(&m,NULL);
sem_init(&full,1,0);
sem_init(&empty,1,buffersize);
counter=0;
}
void * producer(void * p) {
long int pno;
pno=(long int) p;
sem_wait(&empty);
pthread_mutex_lock(&m);
item=rand()%10;
printf("\nP[%ld] producer produce item=%d", pno,item);
buffer[counter++]=item;
pthread_mutex_unlock(&m);
sem_post(&full);
pthread_exit(NULL);
}
void * consumer(void * c)
{
int item;
long int cno;
cno=(long int) c;
sem_wait(&full);
pthread_mutex_lock(&m);
item=buffer[--counter];
printf("\nC[%ld] consumer consumed the item= %d", cno,item);
pthread_mutex_unlock(&m);
sem_post(&empty);
pthread_exit(NULL);
}
int main()
{
int n1, n2;
long int i;initialize();
printf("\n Enter the no of producers: ");
scanf("%d", &n1);
printf("\n Enter the no of consumers: ");
scanf("%d", &n2);
for (i = 0; i < n1; i++)
pthread_create(&tidP[i], NULL, producer,(void *) i);
for (i = 0; i < n1; i++)
pthread_join(tidP[i], NULL);
for (i = 0; i < n2; i++)
pthread_create(&tidC[i], NULL, consumer, (void *) i);
for (i = 0; i < n2; i++)
pthread_join(tidC[i], NULL);
exit(0);
return 0;
}

