# script.sh
# Compilación y ejecución de la Práctica 2 de Compiladores e Intérpretes

flex anLexico.l
mv lex.yy.c anLexico.c
gcc *.c -o Compiladores-2
./Compiladores-2
