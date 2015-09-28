
/********************************************
        TABLA DE SÍMBOLOS HEADER
 ********************************************/

#ifndef TABSIMBOLOS_H
#define	TABSIMBOLOS_H

//Estructura onde gardamos o numero e o lexema
typedef struct {
    int numID;
    char *lexema;
    double valor;
} tipoelem;

//Estructura para insertar na árbore
struct celda {
    tipoelem info;
    struct celda *izq, *der;
};
typedef struct celda * abb;

//Creación da árbore
abb arbore;

void creaArbol(abb *A);
void inicializaArbol(abb *A);
void destruyeArbol(abb *A);
unsigned esVacio(abb A);
void insertaArbol(abb *A, char *lexema, int numID, double valor);
void inserta(abb *A, tipoelem E);
void info(abb A, tipoelem *E);
int esMiembroArbol(abb A, char *lexema);
double devuelveValor(abb A, char *lexema);
abb izq(abb A);
abb der(abb A);


#endif
