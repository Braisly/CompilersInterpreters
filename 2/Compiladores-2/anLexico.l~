
/********************************************
        ANALIZADOR LÉXICO
 ********************************************/

%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "anLexico.h"
#include "tabSimbolos.h"
#include "def.h"
#include "xesErro.h"
int nLinea=1,band=0; 
char *lexema;
%}

/*Creacion: Expresions Regulares*/

COMENTARIOS "#".*|"#="(.|\n)*"=#"
CADENAS "(\""[^\"]*"\")"
ID_RESERVADA [a-zA-Z][a-z_A-Z0-9]*
OP_SIMPLES "+"|"-"|">"|"<"|"/"|","|"("|")"|"*"|"^"|";"|"="
OP_INCREMENTO "+="
OP_DECREMENTO "-="
OP_MAYOR_IGUAL ">="
OP_MENOR_IGUAL "<="
OP_COMPARACION "=="
OP_OR "||"
OP_AND "&&"
OP_DIVISION_LOGICA "//"
N_ENTERO [0-9]+
N_REAL	[+-]?{N_ENTERO}.{N_ENTERO}
N_HEXADECIMAL  "0x"[0-9a-fA-F]+
ESPACIOS [ \t]*
LINEAS [\n]

ERROS [^{COMENTARIOS}{CADENAS}{ID_RESERVADA}{OP_SIMPLES}{OP_INCREMENTO}{OP_DECREMENTO}{OP_MAYOR_IGUAL}{OP_MENOR_IGUAL}{OP_COMPARACION}{OP_OR}{OP_AND}{OP_DIVISION_LOGICA}{N_ENTERO}{N_REAL}{N_HEXADECIMAL}{ESPACIOS}{LINEAS}]

%%


{COMENTARIOS} {
if(yytext[0]=='\n')
	nLinea++;
}
{CADENAS} {return CADENA;}
{ID_RESERVADA} {
	int numID=0;
	lexema=(char *) realloc(lexema, (strlen(yytext) * sizeof(char)));
	strcpy(lexema,yytext);
	numID=esMiembroArbol(arbore, lexema);
	if(numID==IDENTIFICADOR || numID==0)
	{
	 numID=IDENTIFICADOR;
	 band=1;
	}

        return numID;
}

{OP_SIMPLES} {return yytext[0];}
{OP_INCREMENTO} {return INCREMENTO;}
{OP_DECREMENTO} {return DECREMENTO;}
{OP_MAYOR_IGUAL} {return MAYOR_IGUAL;}
{OP_MENOR_IGUAL} {return MENOR_IGUAL;} 
{OP_COMPARACION} {return COMPARACION;}
{OP_OR} {return OR;}
{OP_AND} {return AND;}
{OP_DIVISION_LOGICA}  {return DIVISION_LOGICA;}
{N_ENTERO} {return ENTERO;}
{N_REAL} {return REAL;}
{N_HEXADECIMAL} {return HEXADECIMAL;}
<<EOF>> {return FINAL;}
{LINEAS}  nLinea++;	
{ESPACIOS}
{ERROS} {	

	xestionErros(1,1, nLinea);

    	}

%%


//Función para reservar memoria para cargar o lexema na estructura tipoelem
void cargarTipoelem(tipoelem *elem)
{
 int aux=0;   
 aux=strlen(lexema);
 elem->lexema = (char *) calloc(aux+1, sizeof (char));
 strcpy(elem->lexema, lexema);   
 free(lexema); 
}
//Función para abrir o arquivo
void abrirArquivo()
{
  yyin=fopen("bisection.jl","r");
  if(!yyin)//Si o arquivo non abre ben
  printf("\n\nERRO\n\n");  
}
//Función para cerrar o arquivo
void pecharArquivo()
{
 fclose(yyin);
}

//Función que devolve ao analizador sintáctico o lexema co seu código, nel fanse as chamadas ao resto das funcións
tipoelem automataPrincipal() 
{
    int erro=0,estado=0;
    char aux;
    tipoelem elem;
    elem.numID=0;

    	lexema = (char *) calloc(2, sizeof (char));//Reservamos memoria para o lexema (un caracter)
   	elem.numID=yylex();
    	if(elem.numID==FINAL)
    	{//Si encontramos o final de ficheiro, reservamos memoria e copiamos EOF para detectar o final do arquivo 
     		lexema=(char *) realloc(lexema, 4);
     		strcpy(lexema, "EOF");
    	}
    	

     cargarTipoelem(&elem);//Cargar os datos na estructura tipoelem
     if (band==1) 
           inserta(&arbore, elem);//Si e un identificador e non esta na tabla de simbolos, introducimolo
    band=0;//Reiniciamos a bandeira, que controla si e palabra reservada ou non
    return elem;//Devolvemos o lexema co seu numero para que o utilice o analizador sintactico
}


