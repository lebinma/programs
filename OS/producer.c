//PRODUCER CONSUMER PROBLEM
/* Copyright (C) 2016, Lebin Mathew Alex. All rights reserved.*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex, full, empty;
int bufferSize, buffer[10], bufferIndex=0;

void *producer(void *);     //producer thread routine
void *consumer(void *);     //consumer thread routine
void addItem(int);          //add item to buffer
int removeItem();           //remove item from buffer

void main()
{
    pthread_t id1, id2;     //create thread ids

    printf("Enter the size of buffer : ");
    scanf("%d", &bufferSize);

    //initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, bufferSize);

    //create threads
    pthread_create(&id1, NULL, producer, NULL);
    pthread_create(&id2, NULL, consumer, NULL);

    //wait for the threads to finish
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
}

void *producer(void *arg)
{
    int item;

    while(1)
    {
        item = rand() % 100;    //produce an item

        sem_wait(&empty);   //wait till atleast one is empty
        sem_wait(&mutex);   //wait till buffer is free

        addItem(item);   //produce an item
        sleep(1);

        sem_post(&mutex);   //released mutex
        sem_post(&full);    //finish producing an item

        printf("Producer produced item %d\n", item);
    }   

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;

    while(1)
    {  
        sem_wait(&empty);   //wait till atleast one is full
        sem_wait(&mutex);   //wait till buffer is free

        item = removeItem();    //remove an item
        sleep(1);

        sem_post(&mutex);   //released mutex
        sem_post(&empty);    //consumed an item

        printf("Consumer consumed item %d\n", item);
    }

    pthread_exit(NULL);
}

void addItem(int item)
{
    if (bufferIndex < bufferSize)
    {
        buffer[bufferIndex++] = item;   //add an item at index
    }
    else
    {
        printf("Underflow : Buffer is empty.\n");
    }
}

int removeItem()
{
    if (bufferIndex > 0)
    {
        return buffer[--bufferIndex]; //remove an item from index
    }
    else
    {
        printf("Overflow : Buffer is full.\n");
    }
}