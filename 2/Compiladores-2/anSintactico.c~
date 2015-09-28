
/********************************************
        ANALIZADOR SINTÁCTICO
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabSimbolos.h"
#include "anLexico.h"
#include "def.h"

//Función do analizador sintáctico
void analizadorSintactico() 
{
    abrirArquivo();
    tipoelem elem;
    creaArbol(&arbore);//Creamos e inicializamos a árbore cas palabras reservadas
    inicializaArbol(&arbore);
    while(strcmp(elem.lexema, "EOF")!=0)//Mentres non encontremos o final do arquivo
    {
     elem=automataPrincipal();//Pedimos ao analizador léxico un lexema co seu codigo
     if(strcmp(elem.lexema, "EOF")!=0)
        if(elem.numID==IDENTIFICADOR)//Si é un identificador, imprimimos o numero do identificador e o lexema
            printf("<%d> (%s)\n", elem.numID, elem.lexema);
        else 
            printf("<%d>\n", elem.numID);//Si non e identificador, imprimimos o codigo correspondente ao componente lexico encontrado
    }
    destruyeArbol(&arbore);
    pecharArquivo();	
}

