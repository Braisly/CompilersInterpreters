# script.sh
# Compilación y ejecución de la Práctica 3 de Compiladores e Intérpretes

bison -d anSintactico.y
flex anLexico.l
gcc *.c -o calcular -lfl -lm
