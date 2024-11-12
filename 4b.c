#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t rd[10], wrt[10];
pthread_mutex_t mutex, wrt_mutex;

int rcount = 0, data = 0;

void *reader(void *p) {
    long int rno = (long int)p;

    pthread_mutex_lock(&mutex);
    rcount++;

    if (rcount == 1) { // First reader locks the writer mutex
        pthread_mutex_lock(&wrt_mutex);
    }

    pthread_mutex_unlock(&mutex);

    printf("\nReader %ld reads data as %d", rno + 1, data);

    pthread_mutex_lock(&mutex);
    rcount--;

    if (rcount == 0) { // Last reader unlocks the writer mutex
        pthread_mutex_unlock(&wrt_mutex);
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *writer(void *c) {
    long int wno = (long int)c;

    pthread_mutex_lock(&wrt_mutex); // Writer waits for all readers
    data = rand() % 10;
    printf("\nWriter %ld writes/updates data in dataset as %d", wno + 1, data);
    pthread_mutex_unlock(&wrt_mutex);
}

int main() {
    int nr, nw;
    unsigned long int i, j;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt_mutex, NULL);

    printf("\nEnter the number of readers: ");
    scanf("%d", &nr);
    printf("\nEnter the number of writers: ");
    scanf("%d", &nw);

    for (i = 0; i < nr; i++) {
        pthread_create(&rd[i], NULL, reader, (void *)i);
    }
    
    for (i = 0; i < nr; i++) {
        pthread_join(rd[i], NULL);
    }

    for (j = 0; j < nw; j++) {
        pthread_create(&wrt[j], NULL, writer, (void *)j);
    }

    for (j = 0; j < nw; j++) {
        pthread_join(wrt[j], NULL);
    }

    exit(0);
}

/*
svpmit23@svpmit23-HP-EliteDesk-800-G2-SFF:~/AnishaOsPracticals$ gcc P4B.c -lpthread
svpmit23@svpmit23-HP-EliteDesk-800-G2-SFF:~/AnishaOsPracticals$ ./a.out

Enter the number of readers: 5

Enter the number of writers: 3

Reader 1 reads data as 0
Reader 2 reads data as 0
Reader 3 reads data as 0
Reader 4 reads data as 0
Reader 5 reads data as 0
Writer 1 writes/updates data in dataset as 3
Writer 3 writes/updates data in dataset as 6
Writer 2 writes/updates data in dataset as 7
*/
