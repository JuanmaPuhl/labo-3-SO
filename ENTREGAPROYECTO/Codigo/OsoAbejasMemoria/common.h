#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>

#define MAXPORCIONES 3

/**Estructura auxiliar para almacenar los semaforos en la memoria compartida.*/
typedef struct estructura{
    sem_t abejas;
    sem_t tarroVacio;
    sem_t tarroLleno;
    sem_t oso;
} aux;

key_t generateKey() {
	int projectId = 14;
	char path[200];
	getcwd(path, 200 * sizeof(char));
	key_t key = ftok(path, projectId);
	return key;
}
