/************************************
         XESTION DE ERROS
*************************************
 * 
 * Os erros son clasificados en 4 tipos: - Erros automataPrincipal      tipo=1
 *                                       - Erros automataID_Reservada   tipo=2
 *                                       - Erros automataNumeros        tipo=3     
 *                                       - Erros automataOperadores     tipo=4
 *                                       - Erros automataCadenas        tipo=5
 * Dentro dos tipos de erros, existen subtipos máis específicos. Como por exemplo nos números.
 */

#include <stdio.h>
#include <stdlib.h>
#include "xesErro.h"


void xestionErros(int tipo, int subtipo, int nLinea)
{   
    if(tipo==1)
        printf("Linea: %d - Erro simbolo non reconocido (automataPrincipal)\n", nLinea);
    else if(tipo==2)
           printf("Linea: %d - Erro en palabra (automataID_Reservada)\n", nLinea);
         else if(tipo==3){
              if(subtipo==1)
                 printf("Linea: %d - Erro en numero hexadecimal (automataNumeros)\n",nLinea);
              else if(subtipo==2)
                      printf("Linea: %d - Erro en numero enteiro (automataNumeros)\n",nLinea);
                   else if(subtipo==3)
                          printf("Linea: %d - Erro en numero real (automataNumeros)\n",nLinea);
                       }else if(tipo==4){
                                if(subtipo==1)
                                   printf("Linea: %d - Erro nalgun operador (automataOperadores)\n",nLinea);
                                else if(subtipo==2)
                                        printf("Linea: %d - Erro despois de simbolo menos (-) (automataOperadores)\n",nLinea);
                             }else{if(tipo==5)
                                  printf("Linea: %d - Erro en cadenas de texto (automataCadenas)\n",nLinea);
                             }
                             
    
}