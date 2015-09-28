
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "entrada.h"


FILE *fp;
char *buffer=NULL;
char *inicioLexema=NULL;
char *auxLexema=NULL;
char caracter;



void leerBloques() 
{
    fp = fopen("bisection.jl","r");
    if(fp != NULL)
    {
        buffer = (char *) malloc(32 * sizeof (char));
        fread(buffer, sizeof (char), 32 / 2 - 1, fp);
        buffer[32 / 2 - 1] = EOF;
        buffer[32 - 1] = EOF;
        inicioLexema = buffer;
        auxLexema = buffer;
    } 
    else 
    {
        printf("\n\nError, incapaz de abrir ficheiro.");
        exit(-1);
    }
}

char leerCaracter() 
{
    //int i = 0;
    if(*auxLexema!=EOF) //Si no se apunta a algun EOF PODE PETAR!!!!!!!!!!!!!!!!!!!!!!!!!! 
    {
	 caracter = *auxLexema;
         auxLexema++;
         return caracter;
     }
     else
     {
       if(*auxLexema == &buffer[32 / 2 - 1])//Comprobamos si e o final do primeiro bloque
	{
	  fread(buffer + 32 / 2, sizeof (char), 32 / 2 - 1, fp);//Carga do segundo bloque
	  auxLexema++;
	 }
      }
}
