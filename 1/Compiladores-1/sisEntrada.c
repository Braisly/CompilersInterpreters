
/********************************************
        SISTEMA DE ENTRADA
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sisEntrada.h"
#define tam 50 


//Declaración de variables globales a utilizar nas seguintes funcions
FILE* fp;
char *buf=NULL, *dianteiro, *inicioLexema;
char c;
int band=1;

//Función para cargar o primeiro bloque e poñer o centinela
void cargaBloque1()
{
    int aux=0;
    aux=fread(buf, sizeof (char), tam / 2 - 1, fp);//Cargar o segundo bloque do buffer e gardalo
    if (aux < (tam / 2 - 1)) 
        buf[aux]=EOF;//Cambiar o final do buffer
    else
        buf[tam / 2 - 1]=EOF;//Poñer o final do buffer
}

//Función para cargar o segundo bloque e poñer o centinela
void cargaBloque2()
{
    int aux=0;
    aux = fread(buf + tam / 2, sizeof (char), tam / 2 - 1, fp);//Cargar o segundo bloque do buffer e gardalo
    if (aux < (tam / 2 - 1)) 
        buf[tam / 2 + aux] = EOF;//Cambiar o final do buffer
    else
        buf[tam - 1] = EOF;//Poñer o final do buffer
}

//Funcion para cargar o arquivo en modo lectura e cargar o primeiro buffer
void cargarArquivo()
{ 
    fp=fopen("bisection.jl","r");
    if (fp==NULL)
    {
        printf("\nError, incapaz de abrir o arquivo\n");
        exit(-1);
    }
    else
    {
        buf=(char *) malloc(tam * sizeof (char));//Reservamos memoria para o buffer
        cargaBloque1();
        inicioLexema=buf;//Apuntamos ao inicio do buffer tanto dianteiro 
        dianteiro=buf;
    }
}

//Función para avanzar ao seguiente caracter
char avanzarCaracter()
{
    if (dianteiro==&buf[tam / 2 - 1])//Comprobamos si estamos no EOF do primeiro bloque
    {
        if (band==1)//Bandeira utilizada por si retrocedemos, por defecto band=1 e cargamos o segundo bloque 
            cargaBloque2();
        else 
            band=1;//Si volvemos a un caracter anterior, band=2 e non cargariamos o segundo bloque. Pero volveriamos ao valor por defecto de band
        
        dianteiro++; //Avanzamos no buffer
    } 
    else 
    {
     if (dianteiro==&buf[tam - 1])//Comprobamos si estamos no EOF do segundo bloque 
     {
        if (band==1)//Bandeira utilizada por si retrocedemos, por defecto band=1 e cargamos o primeiro bloque  
            cargaBloque1();
         else 
            band=1;//Si volvemos a un caracter anterior, band=2 e non cargariamos o primeiro bloque. Pero volveriamos ao valor por defecto de band
        dianteiro=buf;//Dianteiro poñelo ao principio do buffer
     } 
    }
    c=*dianteiro;//Gardamos o novo caracter
    dianteiro++;//Avanzamos no buffer
    return c;
}

//Función para volver atrás un caracter
void atrasarCaracter() 
{//Si dianteiro non está na primeira posición do buffer
    if (dianteiro!=buf) 
    {
        dianteiro--;//Retrocedemos
        if (*dianteiro==EOF && dianteiro==&buf[tam/2-1]) //Si estamos no EOF do primeiro bloque, retrocedemos
        {
         dianteiro--;
         band=2;//Cambiamos band, para que non se cargue o segundo bloque (en avanzarCaracter)
        }      
    }
    else 
    {//Si estamos no principio do buffer
      dianteiro=&buf[tam - 2];//Retrocedemos 2 posicións ata a penúltima do segundo bloque
      band=2;//Cambiamos band, para que non se cargue o primeiro bloque (en avanzarCaracter)
    }
}

//Función para volver a empezar o lexema
void resetearLexema() 
{
    inicioLexema=dianteiro;
}

//Función para cerrar o arquivo e liberar a memoria do buffer
void cerrarArquivo()
{
    fclose(fp);
    free(buf);
}
