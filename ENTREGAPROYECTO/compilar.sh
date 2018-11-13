#!/bin/bash
cd Codigo
cd Privilegios
gcc permisos.c -o permisos
cd ..
cd OsoAbejasMensajes
gcc iniciar.c -o inicio
gcc abeja.c -o abeja
gcc oso.c -o oso
cd ..
cd OsoAbejasMemoria
gcc iniciar.c -o inicio -l pthread
gcc abeja.c -o abeja -l pthread
gcc oso.c -o oso -l pthread
cd ..
cd ManejadorMemoria
gcc main.c -o manejador
cd ..
cd Secuencias
cd Secuencia1
gcc main.c -o sec1
cd ..
cd Secuencia2
gcc main.c -o sec2
cd ..
cd Secuencia2B
gcc main.c -o sec2B
cd ..
cd Secuencia3
gcc main.c -o sec3
cd ..
cd Secuencia3B
gcc main.c -o sec3B
cd ..
cd ..

echo Compilacion exitosa.
