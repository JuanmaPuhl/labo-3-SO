#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXCONSUMERS 1
#define MAXPRODUCERS 1
#define BUFFERSIZE 20

sem_t fillCount;
sem_t emptyCount;

void* fConsumidor(void* arg){
    while(1){
        sem_wait(&fillCount);
        printf("[Consumidor] Tomo el pan desde la cola.\n");
        sem_post(&emptyCount);
        sleep(2);
        printf("[Consumidor]Que rico pancito!!.\n");
    }
}

void* fProductor(void* arg){
    while(1){
        printf("[Productor]Creo un pan\n");
        sleep(2);
        sem_wait(&emptyCount);
        printf("[Productor]Agrego el pan\n");
        sem_post(&fillCount);
    }
}

int main()
{
    sem_init(&fillCount,0,0);
    sem_init(&emptyCount,0,BUFFERSIZE);
    pthread_t consumidor[MAXCONSUMERS];
    pthread_t productor[MAXPRODUCERS];
    int i;
    for(i=0; i<MAXCONSUMERS; i++){
        pthread_create(&consumidor[i],NULL,fConsumidor,(void*)&i);
    }
    for(i=0; i<MAXPRODUCERS; i++){
        pthread_create(&productor[i],NULL,fProductor,(void*)&i);
    }

    pthread_join(productor[0],NULL);
    pthread_join(consumidor[0],NULL);
    printf("Hello world!\n");
    return 0;
}
