#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "parser.h"
#include "semantic.h"

char *diccionario[100];
char mensaje[200];
int cantVar = 0;

void agregar(char* s){
  diccionario[cantVar] = malloc(100);
  strcpy(diccionario[cantVar],s);
  cantVar++;
}

int buscar(char* s){
  for(int i=0; i<cantVar;i++){
    if(strcmp(diccionario[i], s) == 0)
      return 1;
  }
  return 0;
}

int declararVar(char* s){
  if (buscar(s)!=1){
    agregar(s);
    generar("Declare", s, "Integer", "");
    return 1;
  }else{
    strcpy(mensaje, "Error semántico: identificador ");
    strcat(mensaje, s);
    strcat(mensaje, " ya declarado");
    yyerror(mensaje); 
    return 0;
  }
}
