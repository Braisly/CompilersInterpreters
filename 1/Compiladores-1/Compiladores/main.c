
/********************************************
        SISTEMA DE ENTRADA
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sisEntrada.h"
#include "anSintactico.h"


int main() 
{
 cargarArquivo();
 analizadorSintactico();//Accedemos a funcion do analizador sintactico
 cerrarArquivo();
}

