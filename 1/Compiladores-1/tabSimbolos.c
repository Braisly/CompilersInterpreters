
/********************************************
        TABLA DE SÍMBOLOS
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabSimbolos.h"
#include "def.h"

//Función de creación da árbore
void creaArbol(abb *A) 
{
    *A = NULL;
}

//Inicializamos a árbore, insertando as palabras reservadas
void inicializaArbol(abb *A)
{
  insertaArbol(A, "if", IF);
  insertaArbol(A, "end", END);
  insertaArbol(A, "error", ERROR);  
  insertaArbol(A, "function", FUNCTION);  
  insertaArbol(A, "try", TRY);
  insertaArbol(A, "while", WHILE);  
  insertaArbol(A, "else", ELSE);  
  insertaArbol(A, "sign", SIGN);  
  insertaArbol(A, "else", ELSE);  
  insertaArbol(A, "catch", CATCH);  
  insertaArbol(A, "println", PRINTLN);
  insertaArbol(A, "return", RETURN);  
  insertaArbol(A, "eps", EPS);    

  
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
//Función de insercción no arbol
void insertaArbol(abb *A, char *palabra, int codigo) {
    tipoelem E;
    E.numID = codigo;
    E.lexema=(char*)malloc(strlen(palabra)*sizeof(char));
    strcpy(E.lexema, palabra);
    inserta(A, E);
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
