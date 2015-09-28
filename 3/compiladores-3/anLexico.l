/********************************************
        ANALIZADOR LÉXICO
 ********************************************/


%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tabSimbolos.h"
#include "def.h"
#include "anSintactico.tab.h"
#include "xesErro.h"

int nLinea=0,band=0; 
//char *lexema;
%}

/*Creacion: Expresions Regulares*/

ID [a-zA-Z][a-z_A-Z0-9]*
RESERVADAS "sin"|"cos"|"tan"|"sqrt"|"log"|"exp"|"log10"
OP_SIMPLES "+"|"-"|"/"|"("|")"|"*"|"^"|";"|"="
N_ENTERO [0-9]+
N_REAL	{N_ENTERO}.{N_ENTERO}
ESPACIOS [ \t]*
LINEAS [\n]

ERROS [^{OP_SIMPLES}{N_ENTERO}{N_double}{ESPACIOS}{LINEAS}]

%%

({N_ENTERO}|{N_REAL}) {
	yylval.real=atof(yytext);
	return TKN_REAL;
}


{RESERVADAS} {//Una vez sea una de las palabras reservadas, comprobamos cual es
	int numID=0;
	yylval.cadena=(char *) malloc(strlen(yytext) + 1);
	strcpy(yylval.cadena,yytext);
	numID=esMiembroArbol(arbore, yytext);
	//printf("\nQUE TIPO DE VARIABLE ES: %d", numID);
	if(numID==SIN)
	 	return TKN_SIN;
	else
	 if(numID==COS)
		return TKN_COS;
	 else
	  if(numID==TAN)
	 	return TKN_TAN;
	  else
	   if(numID==RAIZ)
		return TKN_RAIZ;
	   else
	    if(numID==LOG)
		return TKN_LOG;
	     else
	      if(numID==EXP)
		return TKN_EXP;
   	      else
	        if(numID==ABS)
		  return TKN_ABS;
	        else
	         if(numID==LOG10)
		  return TKN_LOG10;	
}

{ID} {
	int numID=0;
	yylval.cadena=(char *) malloc(strlen(yytext) + 1);
	strcpy(yylval.cadena,yytext);
	return TKN_ID;
}

{OP_SIMPLES} {
		if(yytext[0]=='+')
			return TKN_SUMA;
		else
		 if(yytext[0]=='-')
			return TKN_RESTA;
		 else
		  if(yytext[0]=='/')
			return TKN_DIVISION;
		  else
		   if(yytext[0]=='*')
			return TKN_MULTIPLICACION;
		   else
		     if(yytext[0]=='^')
			return TKN_POTENCIA;
		     else
		      if(yytext[0]=='=')
			return TKN_IGUAL;
		      else
		        if(yytext[0]==';')
				return TKN_FINSENTENCIA;
			else
			  if(yytext[0]=='(')
				return TKN_ABREPARENTESIS;
			  else
			    if(yytext[0]==')')
				return TKN_CIERRAPARENTESIS;				
}


 		


{LINEAS}  nLinea++;	
{ESPACIOS}
{ERROS} {	

	xestionErros(1,1, nLinea);

    	}


%%

