/**Incluyo librerias a utilizar*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

/**Defino constantes*/
#define ROJO "\E[0;31m"
#define VERDE "\E[0;32m"
#define CERRAR "\E[00m"

/**Metodo auxiliar que controla que se haya ingresado la cantidad necesaria de parametros.*/
int validarParametros(int argc){
    /**En este caso no se ingreso ningun parametro.
    Se cuenta 1 extra por la llamada al programa.*/
    if(argc==1){
        printf("%sERROR 1. NO SE INGRESARON PARAMETROS.%s\n",ROJO,CERRAR);
        putc(0x07, stdout);
        exit(-1);
    }
    /**En este caso se ingresaron muchos mas parametros de los necesarios.
    Solo se necesita 1 para la direccion y de 1 a 3 para el modo.
    Se cuenta 1 extra por la llamada al programa.*/
    if(argc>3){
        printf("%sERROR 2. DEMASIADOS PARAMETROS.%s\n",ROJO,CERRAR);
        putc(0x07, stdout);
        exit(-2);
    }
    /**En este caso solo se ingreso la direccion sin especificar modos.
    Se cuenta 1 mas por la llamada al programa.*/
    if(argc==2){
        printf("%sERROR 3. PARAMETROS INSUFICIENTES.%s\n",ROJO,CERRAR);
        putc(0x07, stdout);
        exit(-3);
    }
    return 1;
}

/**Metodo auxiliar que verifica que el modo ingresado tenga valores correctos*/
int validarModo(char* modo){
    /**Verifico que el modo ingresado sea valido.*/
    int val=atoi(modo); //Convierto a entero
    int tam=strlen(modo); //Calculo la cantidad de caracteres
    if(tam<3 || tam>3 || val>777 || val<0){ //Si esta fuera de los rangos permitidos
        printf("%sERROR 4. MODO INVALIDO.%s\n",ROJO,CERRAR); //ERROR
        putc(0x07, stdout); //PIP
        exit(-4);
    }
    /**Veo que ningun digito sea mayor a 7*/
    int ultimo,j;
    for(j=0;j<3;j++){
        ultimo=val%10;
        val/=10;
        if(ultimo>7){
            printf("%sERROR 4. MODO INVALIDO.%s\n",ROJO,CERRAR); //ERROR
            putc(0x07, stdout); //PIP
            exit (-4);
        }
    }
    return 1;
}

/**Metodo principal*/
int main(int argc, char* argv[]){
    validarParametros(argc);//Valido la cantidad de parametros.
    /**Cargo los valores en las variables*/
    char dir[100];
    strcpy(dir,argv[1]); //Guardo en la variable dir, la direccion del archivo ingresada.
    char direccion[102]="/";
    strcat(direccion,dir); //Concateno un / para evitar errores.
    char cero[5]="0";
    char modo[4];
    strcpy(modo,argv[2]); //Guardo en la variable modo los permisos ingresados.
    validarModo(modo); //Valido el modo
    char* mode=strcat(cero,modo); //Pongo un 0 al principio para que lo tome como octal.
    /**Debo pasar modo a octal para que pueda ser leido por chmod*/
    int i=strtol(mode,0,8); //Convierto a octal
    /**Si no es un numero mayor a 0 entonces hay algun problema con el numero ingresado.*/
    int resultado=chmod(direccion,i); //Cambio privilegios
    if(resultado<0){ //Hubo error
        printf("%sERROR AL ACTUALIZAR PERMISOS. ERRNO:%d.%s\n",ROJO,errno,CERRAR);
        putc(0x07, stdout);
    }
    else //Actualizacion correcta.
        printf("%sSe actualizaron los permisos con exito.%s\n",VERDE,CERRAR);
    return 0;
}
