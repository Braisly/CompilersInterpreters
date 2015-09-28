%{
/********************************************
        ANALIZADOR SINTÁCTICO
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tabSimbolos.h"
#include "def.h"
/*#define YYSTYPE double;*/


extern int yylex(void);
extern char *yytext;
extern int nLinea;
extern FILE *yyin;
void yyerror(char *s);


%}

/*Seccion da declaracion dos TOKENS*/

%union
{
	double real;
	char *cadena;
}



%start Calculadora


/*Especificacion dos TOKENS e das súas propiedades*/
%token <entero> TKN_ENTERO;
%token <real> TKN_REAL;
%token <cadena> TKN_ID
%token <cadena> TKN_RESERVADA;
%token TKN_SIN;
%token TKN_COS;
%token TKN_TAN;
%token TKN_RAIZ;
%token TKN_LOG;
%token TKN_EXP;
%token TKN_ABS;
%token TKN_LOG10;
%token TKN_SUMA;
%token TKN_RESTA;
%token TKN_DIVISION;
%token TKN_MULTIPLICACION;
%token TKN_POTENCIA;
%token TKN_IGUAL;
%token TKN_FINSENTENCIA;
%token TKN_ABREPARENTESIS;
%token TKN_CIERRAPARENTESIS;


/*Especificar a asociatividad dos TOKENS*/
%right TKN_IGUAL
%left TKN_SUMA TKN_RESTA
%left TKN_MULTIPLICACION TKN_DIVISION
%right TKN_POTENCIA 


/*Tipo dun non terminal*/
%type <real> asignaciones
%type <real> expresion
%type <real> funciones


%%
/*Seccion das reglas e accions*/

Calculadora:   /* vacío */ | Calculadora linea;


linea:	'\n' |  
	TKN_ID TKN_IGUAL expresion TKN_FINSENTENCIA
	{
	  insertaArbol(&arbore,$1,IDENTIFICADOR,$3);//Insertamos no arbol o novo valor do identificador
		       printf ("%s = %f\n",$1,$3);//Imprimos o resultado de cada linea
	};

expresion: expresion TKN_SUMA expresion { $$=$1+$3; } |
	   expresion TKN_RESTA expresion { $$=$1-$3; } | 
	   expresion TKN_MULTIPLICACION expresion { $$=$1*$3; } |
	   expresion TKN_DIVISION expresion { $$=$1/$3; } |
	   expresion TKN_POTENCIA expresion { $$=pow($1,$3); } |
	   TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS {$$=$2;} |
	   funciones |
           asignaciones;

funciones: TKN_SIN TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=sin($3*M_PI/180); } |
           TKN_COS TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=cos($3*M_PI/180); } |
           TKN_TAN TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=tan($3*M_PI/180); } |
 	   TKN_LOG TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=log($3); } |
           TKN_LOG10 TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=log10($3); } |
           TKN_RAIZ TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=sqrt($3); } |
           TKN_EXP TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=exp($3); } |
           TKN_ABS TKN_ABREPARENTESIS expresion TKN_CIERRAPARENTESIS { $$=abs($3); };

asignaciones: TKN_REAL { $$=$1; } |
	      TKN_ID { float aux=0;
		       aux = devuelveValor(arbore,$1);
                       $$ = aux;
           	};





%%

/*Seccion de rutinas de usuario*/


void yyerror(char *tipo)
{
 printf("Tipo de error: %s\n",tipo);
}

int main(int argc,char **argv)
{   int band=0;	
    tipoelem elem;
    creaArbol(&arbore);//Creamos e inicializamos a árbore cas palabras reservadas
    inicializaArbol(&arbore);
    if(argc>1)
    {
	if(yyin=fopen(argv[1],"rt"))
		band=1;
    }else
	yyin=stdin;
    yyparse();    
    printf("Numero lineas analizadas: %d\n",nLinea);
    destruyeArbol(&arbore);
    if(band==1)//Cerramos o arquivo
	 fclose(yyin);
    return 0;	
}

