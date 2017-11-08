#include "symbol.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

char infijo[10];
int cant_temps = 1;
char mensaje[200];


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
    char aux[10] = "";
    strcpy(aux, op_b);

    printf("Llega infijo %s\n",infijo );
    printf("Llega op_a %s\n", op_a );
    printf("Llega op_b %s\n", op_b );

    char temp_nro[2];
    strcpy(infijo,"temp#");
    sprintf(temp_nro, "%d", cant_temps);
    strcat(infijo, temp_nro);
    cant_temps++;

    printf("Prima infijo %s\n",infijo );
    printf("Prima op_a %s\n", op_a );
    printf("Prima op_b %s\n", op_b );

    declararVar(infijo);

    switch(operacion){
        case '+':
            generar("ADD", op_a, aux, infijo);
            break;

        case '-':
            generar("SUBS", op_a, aux, infijo);
            break;

        case '*':
            generar("MULT", op_a, aux, infijo);
            break;

        case '/':
            generar("DIV", op_a, aux, infijo);
            break;

        case 'N':
            generar("INV", op_a, "", infijo);
            break;
    }
    printf("Mando infijo %s\n",infijo );
    return infijo;
}
