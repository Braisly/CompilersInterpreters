/************************************
         XESTION DE ERROS
*************************************
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "xesErro.h"


void xestionErros(int tipo, int subtipo, int nLinea)
{   
    if(tipo==1)
        printf("Linea: %d - Erro simbolo non reconocido\n", nLinea);
}
