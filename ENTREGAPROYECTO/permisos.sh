#!/bin/bash
cd Codigo
cd Privilegios
echo Ingrese la direccion.
read var1
echo Ingrese los permisos
read var2
./permisos $var1 $var2 
