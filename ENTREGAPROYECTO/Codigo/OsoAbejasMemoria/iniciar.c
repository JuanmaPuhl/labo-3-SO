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

int main(){
    int i;

    /**Creo la clave*/
    key_t llave = generateKey();

    /**Creo la zona de memoria compartida*/
    int sector=shmget(llave,sizeof(aux),0660 | IPC_CREAT);
    //Mensaje si se produjo error.
    if(sector == -1){
        perror("Ocurrio un error: shmget");
        exit(1);
    }
    /**Creo el puntero a la zona de memoria.*/
    aux *estruct=(aux*) shmat(sector,(char*)0,0);
    //Mensaje si se produjo error.
    if(estruct==(void*) -1){
        perror("Ocurrio un error: shmat");
        exit(1);
    }

    /**Debo inicializar los semaforos dentro de la estructura*/
    sem_init(&estruct->abejas,1,1);
    sem_init(&estruct->oso,1,0);
    sem_init(&estruct->tarroVacio,1,MAXPORCIONES);
    sem_init(&estruct->tarroLleno,1,0);
    printf("Region de memoria creada con exito.\n");
    printf("Presione ENTER para finalizar.\n");
    /**Espero a que el usuario presione ENTER para terminar la ejecucion.*/
    char c='.';
    while(c!='\n'){
        c=getchar();
    }

    /**Elimino la zona de memoria compartida*/
    int eliminarMemoria=shmdt(estruct);
    if(eliminarMemoria==-1){
        perror("Ocurrio un error: shmdt");
        exit(1);
    }
    eliminarMemoria=shmctl(sector,IPC_RMID,(struct shmid_ds *)NULL);
    if(eliminarMemoria==-1){
        perror("Ocurrio un error: shmctl");
        exit(1);
    }
    printf("Finalizacion exitosa.\n");
    return 0;
}
