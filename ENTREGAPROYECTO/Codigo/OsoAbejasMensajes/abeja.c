#include "common.h"

/**Funcion ejecutada por las abejas para llenar el tarro de miel*/
void llenarTarro(int identificador){
    /**Creo los tipos de mensajes con los que trabajara la funcion.*/
    aux abejas,oso,tarroVacio,tarroLleno;
    //Establezco los tipos
    abejas.tipo=1;
    oso.tipo=2;
    tarroVacio.tipo=3;
    tarroLleno.tipo=4;
	while(1){
		//Espero a que llegue un mensaje abeja.
		msgrcv (identificador,(struct msgbuf *)&abejas, TAM,1, 0);
		//Espero a que llegue un mensaje tarroVacio.
		msgrcv (identificador,(struct msgbuf *)&tarroVacio, TAM,3,0);
		//Envio un mensaje de tarroLleno.
		msgsnd (identificador,(struct msgbuf *)&tarroLleno, TAM,IPC_NOWAIT);
		printf("[ABEJA] Pongo un poco de miel.\n");
		/**Vuelvo a esperar un mensaje tarroVacio para saber si hay que seguir
		llenando o no, esto puedo saberlo si retorna -1.*/
		if(msgrcv (identificador,(struct msgbuf *)&tarroVacio, TAM,3,IPC_NOWAIT)==-1){
			printf("[ABEJA] LLENE EL TARRO, DESPIERTO AL OSO.\n");
			//Envio un mensaje de tipo oso.
			msgsnd (identificador,(struct msgbuf *)&oso, TAM,IPC_NOWAIT);
		}
		else{
			//Envio un mensaje de tipo tarroVacio
			msgsnd (identificador,(struct msgbuf *)&tarroVacio, TAM, IPC_NOWAIT);
			//Envio un mensaje de tipo abeja
			msgsnd (identificador, (struct msgbuf *)&abejas, TAM, IPC_NOWAIT);
		}
		//Le doy su merecido descanso.
		sleep(2);
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
    llenarTarro(identificador);
}
