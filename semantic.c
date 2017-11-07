#include "symbol.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "parser.h"

int cant_temps = 1;
char mensaje[200];
char infijo[10];

void generar(char* op, char* a, char* b, char* c){
    printf("%s %s, %s, %s\n", op, a, b, c);
}

void comenzar (void){
    generar("Load", "rtlib", "", "");
}

void terminar(){
    generar("Stop", "", "", "");
}

void asignar (char* izquierda, char* derecha) {
    generar("Store", derecha, izquierda, "");
}

void leer_id(char* s){
    generar("Read", s, "Integer", "");
}

void escribir_exp (char* out) {
    generar("Write", out, "Integer", "");
}

int procesar (char* s){
  if(buscar(s)!=1){
    strcpy(mensaje, "Error semántico: identificador ");
    strcat(mensaje, s);
    strcat(mensaje, " NO declarado");
    yyerror(mensaje);
    return 0;
  }else{
    return 1;
  }
}

char* gen_infijo(char* op_a, char operacion, char* op_b){
    /* [IMPORTANTE]
    Hay problemas por aca OBVIAMENTE
    */
    char temp_nro[2];
    strcpy(infijo,"temp#");
    sprintf(temp_nro, "%d", cant_temps);
    strcat(infijo, temp_nro);
    cant_temps++;
    declararVar(infijo);
    switch(operacion){
        case '+':
            generar("ADD", op_a, op_b, infijo);
            break;

        case '-':
            generar("SUBS", op_a, op_b, infijo);
            break;

        case '*':
            generar("MULT", op_a, op_b, infijo);
            break;

        case '/':
            generar("DIV", op_a, op_b, infijo);
            break;

        case 'N':
            generar("INV", op_a, "", infijo);
            break;
    }

    return infijo;
}
