
/********************************************
        ANALIZADOR LÉXICO
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "anLexico.h"
#include "tabSimbolos.h"
#include "sisEntrada.h"
#include "def.h"
#include "xesErro.h"


//Varibles globales empleadas para a construcción do lexema e o numero de linea no que nos encontramos
int nLinea=1,i=0; 
char *lexema;

//Función para reservar memoria para cargar o lexema na estructura tipoelem
void cargarTipoelem(tipoelem *elem)
{
 int aux=0;   
 aux=strlen(lexema);
 elem->lexema = (char *) calloc(aux+1, sizeof (char));
 strcpy(elem->lexema, lexema);   
 free(lexema); 
}

//Función para aumentar o tamaño do lexema
void aumentarLexema()
{
 int aux=0;
 aux=(strlen(lexema) + 1) * sizeof (char);
 lexema=(char *) realloc(lexema, aux+1);
}

//Función que detecta comentarios
void automataComentarios()
{
 int erro=0, estado=0;
 char aux;
 while(!erro)
 {
  switch(estado)
        {
            case 0:
                aux=avanzarCaracter();
                if(aux=='=')//Comprobación de si é un comentario multilinea #=
                    estado=1;
                else
                {//Si non e multilinea estado=2
                 atrasarCaracter();
                 estado=2;
                }
                break;
            case 1://Si e multilinea, ata que atopemos =# non salimos do estado (ata que siga o comentario)
                    aux=avanzarCaracter();
                    while(aux!='=')//
                    {
                      if(aux=='\n')
                        nLinea++;
                      aux=avanzarCaracter();
                    }
                    aux=avanzarCaracter();
                    if(aux=='#')
                        erro=1;
                    else
                        estado=1;
                break;  
            case 2://Cando atopamos \n acabamos o comentario
                while(aux!='\n')
                    aux=avanzarCaracter();
                nLinea++;
                erro=1;
                break;
        }
    }
}

//Función que detecta identificadores e palabras reservadas
int automataID_Reservada(tipoelem *elem, int *band)
{
    char aux;
    int erro=0, numID=0, estado=0;

    while (!erro) 
    {
      switch(estado)
      {
          case 0://Pedimos o seguinte caracter, xa sabemos que e un identificador ou palabra reservada
                 aux=avanzarCaracter();
                 if((isalnum(aux)) || (aux==95))//Si e numero ou letra ou _ estado=1
                     estado=1;
                 else if((aux==' ') || (aux=='\n'))//Si encontramos espacio en blanco ou salto de linea, estado=2 e salimos do automata
                          estado=2; 
                 else if((aux==',') || (aux=='(') || (aux==')') || (aux== '-') || (aux== '+') || (aux=='=') || (aux== '*') || (aux== '.') || (aux== '/') || (aux== '>') || (aux== '<') || (aux=='^'))//Si e un dos seguintes simbolos vamos ao estado=3, e podemos devolver o lexema 
                                estado=3;
                           else  
                               xestionErros(2,1,nLinea);//Si e un simbolo inesperado chamamos a xestion de errores 
              break;
          case 1://Aumentamos o tamaño do lexema e vamos gardando os caracteres
            aumentarLexema(); 
            lexema[i]=aux; 
            lexema[i+1]=0;
            i++;
            estado=0;
              break;
          case 2://Miramos si hai salto de linea e salimos
              if(aux=='\n')
                  nLinea++;
              erro=1;    
              break;
          case 3://Retrocedemos un caracter e xa podemos devovler o lexema
               atrasarCaracter();
               erro=1;
               break;
      }
    } 
    
    numID=esMiembroArbol(arbore, lexema);//Miramos si xa esta na arbore
    if (numID!= IDENTIFICADOR && numID!= 0) 
        elem->numID=numID; //Si e unha palabra reservada gardamos o seu numero
    else{
         elem->numID=IDENTIFICADOR;//Gardamos o numero, de identificador e activamos a bandeira para gardalo na tabla de simbolos
         *band=1;  
    } 
    return 1;       
}

//Función que detecta os tipos de números
int automataNumeros(tipoelem *elem, char caracter)
{
   char aux;
   int erro=0, erro2=0, estado=0, real=0, hexa=0;

    while (!erro) 
    {
        switch (estado)
        {
            case 0:
                   if(caracter==48)//Si o numero leido anteriormente e 0 
                   {
                    aux=avanzarCaracter();
                    if(aux=='x')//HEXADECIMAL, accedemos ao estado=1
                        estado=1;
                    else
                    {
                     atrasarCaracter();
                     estado=2;
                    }       
                   }else estado=2;//Accedemos ao estado=2, descartamos que sexa hexadecimal
                break;
            case 1:
                //HEXADECIMALES
                 aumentarLexema();//Aumentamos tamaño e gardamos o caracter leido   
                 lexema[i]=aux; 
                 lexema[i+1]=0;
                 i++;
                 while(!erro2)
                 {
                     aux=avanzarCaracter();//Avanzamos o caracter e comprobamos si e do tipo hexadecimal
                    if ((isdigit(aux)) || (aux=='A') || (aux=='B')|| (aux=='C')|| (aux=='D')|| (aux=='E') || (aux=='F'))
                    {
                     aumentarLexema();   
                     lexema[i]=aux; 
                     lexema[i+1]=0;
                     i++;   
                     hexa=1;//Numero confirmado como hexadecimal, activamos bandeira de impresion
                    }else if((hexa=1) && ((aux=='(') || (aux==')') ||  (aux==',')  ||  (aux==';') || (aux=='=') || (aux=='+') || (aux=='-') || (aux=='*') || (aux=='|') || (aux=='/') || (aux=='>') || (aux=='<') || (aux==' ') || (aux=='\t') || (aux=='\n')))//Si e un numero hexadecimal e un dos simbolos mostrados,accedemos ao automata de impresion
                         {
                          atrasarCaracter();
                          estado=4;
                          erro2=1;
                         }
                    else//Si non é hexadecimal e non se encontran un dos simbolos indicados, ERRO
                          xestionErros(3, 1, nLinea);      
                    }
                  break;
            case 2://ENTEIROS
                aux=avanzarCaracter();
                if (isdigit(aux)) {//Comprobamos que siga sendo un numero
                    aumentarLexema();
                    lexema[i]=aux;
                    lexema[i+1]=0;
                    i++;
                    estado=2;
                } else if(aux==46)//REAIS, encontramos un punto .
                            estado=3;
                else if((isalpha(aux)) || (aux==',')  ||  (aux==';') || (aux=='(') || (aux== ')') || (aux=='=') || (aux=='+') || (aux=='-') || (aux=='*') || (aux=='|') || (aux=='/') || (aux=='>') || (aux=='<') || (aux==' ') || (aux=='\t') || (aux=='\n')) {//Si e un dos caracteres indicados, accedemos ao estado de impresion estado=4
                                atrasarCaracter();
                                estado=4;
                           }else {//Si non e un caracter dos esperados, erro
                                xestionErros(3, 2, nLinea);
                                estado=2;
                            }
                break;
            case 3:
                //REAIS
                real=1;//Activamos que a bandeira que e un numero real
                aumentarLexema();
                lexema[i]=aux;
                lexema[i+1]=0;
                i++;
                aux=avanzarCaracter();
                if (isdigit(aux)) {//Si e un numero seguimos no mesmo estado
                    estado = 3;
                } else if ((isalpha(aux)) || (aux==',') ||  (aux==';') || (aux== '(') || (aux== ')') || (aux=='=') || (aux=='+') || (aux=='-') || (aux=='*') || (aux=='|') || (aux== '/') || (aux=='>') || (aux=='<') || (aux==' ') || (aux=='\t') || (aux=='\n')) {//Si e un dos seguintes caracteres, vamos ao estado=4, para indicar que e un real
                        atrasarCaracter();
                        estado = 4;
                    } else {//Si non encontramos un caracter esperado, ERRO
                        xestionErros(3,3, nLinea);
                        estado=3;
                    }
                break;
            case 4:
                  //ESTADO 4, gardamos o identificador do tipo de numero
                if(hexa==1)
                    elem->numID=HEXADECIMAL;
                else if(real==1) 
                       elem->numID=REAL;
                     else 
                       elem->numID=ENTERO;  
                erro=1;//Salimos do bucle
                break;
        }
    }
    return 1;    
    
}



//Función que detecta os tipos de operadores: ||, //, ==, >=, <=, +=, -=.
int automataOperadores(tipoelem *elem,char caracter)
{
    int estado=0, erro=0;
    char aux;
    while (!erro) 
    {
      switch(estado)
      {
        case 0:
              if(caracter=='|')//Si o simbolo e |, comprobamos si e un OR indo ao estado=1
                  estado=1;  
              else if(caracter=='/')//Si o caracter e /, comprobamos si se trata dunha division simbolica
                     estado=2;
                   else //Resto de operadores, estado=3    
                     estado=3;
            break;
        case 1:
          aux=avanzarCaracter();
          if(aux=='|')  
              estado=4;
          else
              estado=5;
            break;
        case 2:
          aux=avanzarCaracter();
          if(aux=='/')//Division simbolica atopada, estado=4, estado de asignacion 
              estado=4;
          else//Estado de asignación de division, ou ERRO si o seguinte caracter non e un dos esperados
              estado=5;
            break;           
            break;
        case 3://Leemos o seguinte caracter e miramos si atopamos =, vamos ao estado=4, de asignacion. Pola contra, si atopamos que o caracter inicial era -, interpretamos un numero negativo, estado=6 e si non estado=5
           aux=avanzarCaracter();
          if(aux=='=')
              estado=4;
          else if(caracter=='-')
                  estado=6;//Miramos si se trata dun numero negativo, accedemos ao estado=6
               else    
                  estado=5; //Accedemos ao estado=5, si non atopamos o operador ou e numero negativo
            break;
        case 4://Estado no que gardamos o operador, e asignamos o seu correspondente numero.
              lexema[i]=aux; 
              lexema[i+1]=0;
              i++;
              if(caracter=='|')
                  elem->numID=OR;
              else if(caracter=='/')
                   elem->numID=DIVISION_LOGICA;
                   else if(caracter=='>')
                          elem->numID=MAYOR_IGUAL;
                        else if(caracter=='<')
                                elem->numID=MENOR_IGUAL;
                             else if(caracter=='=')
                                     elem->numID=COMPARACION;
                                  else if(caracter=='-')
                                          elem->numID=DECREMENTO;
                                       else if(caracter=='+')
                                               elem->numID=INCREMENTO;
              erro=1;    
            break;
        case 5://Estado no que comprobamos o caracter seguinte e esperado, gardamos o codigo ascii, do operador empleado
      if ((isalnum(aux))  || aux==' ')
        {
          atrasarCaracter();
          aux=caracter;
          elem->numID=aux;
          erro=1;
        }
      else//Si non se atopa un caracter esperado, ERRO
          xestionErros(4,1,nLinea);  
            break;
          case 6://Estado no que comprobamos que e un numero negativo. Exemplo: -5, si o e accedemos ao automata de numeros.
            if(isalnum(aux))
                erro=automataNumeros(elem,aux);
            else if(aux==' ' || aux=='('){ //Si non sigue un numero comprobamos que sigue un caracter esperado, si o sigue gardamos o valor do simbolo da resta - 
                   atrasarCaracter();
                   aux=caracter;         
                   elem->numID=aux;
                   erro=1;
                 }else//Si non recibimos un caracter esperado, ERRO
                   xestionErros(4,2,nLinea);            
            break;
     }
    }
    return 1;
     
}

//Función que detecta as cadenas de printf ou error
int automataCadenas(tipoelem *elem)
{
 char aux;
      aux=avanzarCaracter();
      if(aux!='"' && aux!='\n')
      {
        while(aux!='"')//Ata que atopemos un cierre de comillas avanzamos caracteres
              aux=avanzarCaracter();
         elem->numID=CADENA;//Detectamos cadena
      }
      else
          xestionErros(5,1,nLinea);
      
 return 1;     
}



//Función que devolve ao analizador sintáctico o lexema co seu código, nel fanse as chamadas ao resto das funcións
tipoelem automataPrincipal() 
{
    int erro=0,estado=0,band=0;
    char aux;
    tipoelem elem;
    elem.numID=0;

    lexema = (char *) calloc(2, sizeof (char));//Reservamos memoria para o lexema (un caracter)

    while (!erro) 
    {
        switch (estado) 
        {
            case 0:
                aux=avanzarCaracter();
                if((aux==' ') || (aux== '\t'))//Comprobamos si hai tabulacion ou espacio 
                    estado=0;
                else if(aux=='\n'){ //Comprobamos si hai salto de linea
                     nLinea++;
                     estado=0;
                    }else if(aux=='#')//Si detectamos un # vamos ao estado=1, automata de comentarios 
                              estado=1; 
                          else if(isalpha(aux))//Si detectamos unha letra vamos ao estado=2, automata de identificadores e palabras reservadas 
                                  estado=2;
                               else if(isdigit(aux))//Si encontramos un numero vamos ao estado=3, automata dos numeros
                                        estado=3;
                                    else if((aux=='>') || (aux=='<') || (aux=='=') || (aux=='|') || (aux=='/') || (aux=='+') || (aux=='-'))//Si encontramos os seguintes simbolos accedemos ao estado=4, automata de operadores
                                            estado=4;
                                         else if(aux=='"')//Si encontramos un ", accedemos ao estado=5, automata de cadenas
                                                estado=5;
                                              else  if((aux==',') || (aux=='(') || (aux==')') || (aux=='*') || (aux=='^') || (aux==';')){//Si encontramos algun destes simbolos gardamos o codigo na estructura tipoelem 
                                                        lexema[i]=aux;
                                                        lexema[i+1]=0;
                                                        erro=1;
                                                        elem.numID=aux;
                                                   }else if(aux==EOF){//Si encontramos o final de ficheiro, reservamos memoria e copiamos EOF para detectar o final do arquivo 
                                                           lexema=(char *) realloc(lexema, 4);
                                                           strcpy(lexema, "EOF");
                                                           erro=1;
                                                        }else 
                                                            xestionErros(1,1, nLinea);
                break;  
            case 1://Accedemos ao automata de comentarios
                automataComentarios();
                estado=0;
                break;
            case 2://Accedemos ao automata de palabra reservada e identificadores
                lexema[i]=aux;
                lexema[i+1]=0;
                i++;
                erro=automataID_Reservada(&elem,&band);
                break;
            case 3://Accedemos ao automata para detectar numeros
                lexema[i]=aux;
                lexema[i+1]=0;
                i++;
                erro=automataNumeros(&elem,aux);
                break;
            case 4://Accedemos ao automata dos operadores
                lexema[i]=aux;
                lexema[i+1]=0;
                i++;
                erro=automataOperadores(&elem,aux);
                break;
            case 5://Accedemos automata de cadenas
                lexema[i]=aux;
                lexema[i+1]=0;
                i++;
                erro=automataCadenas(&elem);
                break;
        }//Salimos do bucle, cando error!=0. Cando entramos nun automata retornamos un valor, con este valor salimos
    }
    
    i=0;
    resetearLexema();//Función para volver a colocar o inicio do proximo lexema
    cargarTipoelem(&elem);//Cargar os datos na estructura tipoelem
    if (band==1) 
           inserta(&arbore, elem);//Si e un identificador e non esta na tabla de simbolos, introducimolo  
    return elem;//Devolvemos o lexema co seu numero para que o utilice o analizador sintactico
}


