#include "common.h"

int main(){
    /**Creo los tipos de mensajes con los que trabajara la funcion.*/
    aux abejas,tarroVacio;
    int identificador;

    /**Obtengo la clave*/
    key_t clave=generateKey();

    /**Creo la cola de mensajes.*/
    identificador = msgget (clave, 0666| IPC_CREAT );
    //Veo si se produjo error.
    if(identificador==-1){
        printf("Error al obtener el identificador.\n");
        exit(1);
    }

    //Seteo los tipos.
    abejas.tipo=1;
    tarroVacio.tipo=3;

    int i;
    /**Para el funcionamiento, utilizo un tipo de mensaje especial, el cual contiene la cantidad
    de porciones a añadirse al tarro.*/
    for(i=0; i<MAXPORCIONES; i++)
    msgsnd (identificador,(struct msgbuf *)&tarroVacio, TAM, IPC_NOWAIT);

    /**Envio un mensaje de abeja.*/
    msgsnd (identificador,(struct msgbuf *)&abejas, TAM, IPC_NOWAIT);
    printf("Se ha iniciado la cola correctamente.\n");
    printf("Presione ENTER para cerrarla.\n");

    /**Espero a que el usuario presione ENTER para terminar la ejecucion.*/
    char c='.';
    while(c!='\n'){
        c=getchar();
    }

    /**Elimino la cola de mensajes.*/
    int borrarCola=msgctl(identificador,IPC_RMID,0);
    if(borrarCola==-1){
        printf("Error al intentar eliminar la cola de mensajes.\n");
        exit(1);
    }

    printf("Finalizacion exitosa.\n");
    return 0;
}
