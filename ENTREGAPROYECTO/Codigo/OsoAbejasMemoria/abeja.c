#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

/**Funcion ejecutada por las abejas para llenar el tarro de miel*/
void llenarTarro(int sector){
    /**Creo un acceso a la memoria compartida.*/
    aux *estruct=(aux*)shmat(sector,(char*)0,0);
    //Mensaje si se produjo error.
    if(estruct==(void*) -1){
        perror("Ocurrio un error: shmat");
        exit(1);
    }

    while(1){
        /**Pongo un bloqueo en la seccion critica.
        De esta forma solo una abeja puede poner miel a la vez.*/
        sem_wait(&estruct->abejas);
        /**Chequeo que el tarro no este lleno.*/
        sem_wait(&estruct->tarroVacio);
        printf("[ABEJA] Pongo un poco de miel.\n");
        sem_post(&estruct->tarroLleno);
        if(sem_trywait(&estruct->tarroVacio)!=0){
            //Cuando ya esta lleno el tarro...
            printf("[ABEJA] LLENE EL TARRO. DESPIERTO AL OSO.\n");
            //Despierto al oso..
            sem_post(&estruct->oso);
        }
        else{
            //Dejo el tarro como estaba
            sem_post(&estruct->tarroVacio);
            //Dejo que otra abeja trabaje
            sem_post(&estruct->abejas);
        }
        //Tiempo de merecido descanso
        sleep(2);
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
    llenarTarro(sector);
}
