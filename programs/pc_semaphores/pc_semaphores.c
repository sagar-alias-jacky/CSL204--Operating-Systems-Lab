#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MaxItems 5
#define BufferSize 5

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d inserted item %d at buffer position %d\n", *((int *)pno), item, in);
        in = (in + 1) % BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumer %d removed item %d at buffer position %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void main()
{
    pthread_t producers[5], consumers[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);
    int id[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
        pthread_create(&producers[i], NULL, (void *)producer, (void *)&id[i]);
    for (int i = 0; i < 5; i++)
        pthread_create(&consumers[i], NULL, (void *)consumer, (void *)&id[i]);
    for (int i = 0; i < 5; i++)
        pthread_join(producers[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(consumers[i], NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}