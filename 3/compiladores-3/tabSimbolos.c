
/********************************************
        TABLA DE SÍMBOLOS
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabSimbolos.h"
#include "def.h"
#include <math.h>

//Función de creación da árbore
void creaArbol(abb *A) 
{
    *A = NULL;
}


//Inicializamos a árbore, insertando as palabras reservadas
void inicializaArbol(abb *A)
{
  insertaArbol(A,"sin",SIN,0);
  insertaArbol(A,"cos",COS,0);
  insertaArbol(A,"tan",TAN,0);
  insertaArbol(A,"pi",PI,M_PI);
  insertaArbol(A,"log",LOG,0);
  insertaArbol(A,"log10",LOG10,0);  
  insertaArbol(A,"raiz",RAIZ,0); 
  insertaArbol(A,"exp",EXP,0);
  insertaArbol(A,"abs",ABS,0);  
}
//Destruimos a arbore
void destruyeArbol(abb *A) {
    if (*A != NULL) {
        destruyeArbol(&(*A)->izq);
        destruyeArbol(&(*A)->der);
        free(*A);
        *A = NULL;
    }
}

//Función de insercción no arbol
void insertaArbol(abb *A, char *lexema, int numID, double valor) {
    tipoelem E;
    E.numID = numID;
    E.lexema=(char*)malloc(strlen(lexema)*sizeof(char));
    E.valor=valor;
    strcpy(E.lexema, lexema);
    inserta(A, E);
}

//Comprobacion de si a árbore esta vacia 
unsigned esVacio(abb A) {
    return A == NULL;
}
//Funcion de inserccion da estructura tipoelem
void inserta(abb *A, tipoelem E) {
    if (esVacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info = E;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    } else if (strcmp(E.lexema, (*A)->info.lexema) < 0) {
        inserta(&(*A)->izq, E);
    } else {
        inserta(&(*A)->der, E);
    }
}

//Función que obten un valor dun nodo da arbore
void info(abb A, tipoelem *E) {
    *E = A->info;
}

//Función que devolve o nodo esquerdo
abb izq(abb A) {
    return A->izq;
}
//Función que devolve o nodo dereito
abb der(abb A) {
    return A->der;
}


//Funcion que comproba que existe un lexema no arbol, e devolve o seu numero correspondente
int esMiembroArbol(abb A, char *lexema) {
    if (esVacio(A))
        return 0;
    else if (strcmp(lexema, A->info.lexema) == 0)
        return A->info.numID;
    else if (strcmp(lexema, A->info.lexema) < 0)
        return esMiembroArbol(A->izq, lexema);
    else if (strcmp(lexema, A->info.lexema) > 0)
        return esMiembroArbol(A->der, lexema);
    return 0;
}


//Funcion que combrueba que existe dicho lexema, y devuelve su valor actual
double devuelveValor(abb A, char *lexema) {
    if (esVacio(A))
        return 0;
    else if (strcmp(lexema, A->info.lexema) == 0)
        return A->info.valor;
    else if (strcmp(lexema, A->info.lexema) < 0)
        return devuelveValor(A->izq, lexema);
    else if (strcmp(lexema, A->info.lexema) > 0)
        return devuelveValor(A->der, lexema);
    return 0;
}
