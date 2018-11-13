#include "common.h"

/**Funcion ejecutada por el oso para dormir y comer*/
void funcionOso(int identificador){
    /**Creo los tipos de mensajes con los que trabajara la funcion.*/
    aux abejas,oso,tarroVacio,tarroLleno;
    //Establezco los tipos
    abejas.tipo=1;
    oso.tipo=2;
    tarroVacio.tipo=3;
    tarroLleno.tipo=4;
    while(1){
        //Espero a que llegue un mensaje de tipo oso.
        msgrcv (identificador,(struct msgbuf *)&oso, TAM,2, 0);
        printf("[OSO] ME DESPERTE, VOY A COMER.\n");
        //Consumo la miel y vuelvo a llenar el contador de porciones.
        while(msgrcv(identificador,(struct msgbuf *)&tarroLleno, TAM,4,IPC_NOWAIT)!=-1)
            msgsnd (identificador,(struct msgbuf *)&tarroVacio, TAM, IPC_NOWAIT);
        //Tiempo de espera hasta que come.
        printf("[OSO] YA COMI, VOY A DORMIR .\n");
        sleep(3);
        //Envio un mensaje de tipo abejas.
        msgsnd (identificador,(struct msgbuf *)&abejas, TAM, IPC_NOWAIT);
    }
}

int main(){
    /**Obtengo la clave*/
    key_t clave=generateKey();

    /**Creo la cola de mensajes.*/
    int identificador = msgget (clave, 0666);
    //Veo si se produjo error.
    if(identificador==-1){
        printf("Error al obtener el identificador.\n");
        exit(1);
    }
    funcionOso(identificador);
}
