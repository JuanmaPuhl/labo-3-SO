#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "common.h"

/**Funcion ejecutada por el oso para dormir y comer*/
void funcionOso(int sector){
    /**Creo un acceso a la memoria compartida.*/
    aux *estruct=(aux*)shmat(sector,(char*)0,0);
    //Mensaje si se produjo error.
    if(estruct==(void*) -1){
        perror("Ocurrio un error: shmat");
        exit(1);
    }

    while(1){
        //Bloqueo el acceso hasta que el tarro este lleno.
        sem_wait(&estruct->oso);
        printf("[OSO] ME DESPERTE, VOY A COMER.\n");
        //Mientras el tarro no este vacio...
        //El oso come la miel
        while(sem_trywait(&estruct->tarroLleno)==0)
            sem_post(&estruct->tarroVacio);
        printf("[OSO] YA COMI,VOY A DORMIR.\n");
        sleep(3);
        //Ya termino de comer, deja que las abejas trabajen.
        sem_post(&estruct->abejas);
    }
}

int main(){

    /**Creo la clave*/
    key_t llave = generateKey();

    /**Obtengo la zona de memoria compartida*/
    int sector=shmget(llave,sizeof(aux),0660);
    //Mensaje si se produjo error.
    if(sector == -1){
        perror("Ocurrio un error: shmget");
        exit(1);
    }
    funcionOso(sector);
}
