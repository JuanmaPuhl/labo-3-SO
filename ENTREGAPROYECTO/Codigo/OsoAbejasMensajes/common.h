#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

/**Defino constantes con el numero maximo de abejas, de porciones y de osos.*/
#define MAXPORCIONES 3
#define TAM (sizeof(aux)-sizeof(long))

/**Estructura auxiliar para almacenar los datos que necesito para cada mensaje.*/
typedef struct estructura{
    long tipo;
} aux;

key_t generateKey() {
	int projectId = 14;
	char path[200];
	getcwd(path, 200 * sizeof(char));
	key_t key = ftok(path, projectId);
	return key;
}
