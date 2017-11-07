#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "parser.h"
#include "semantic.h"


char *diccionario[100];
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

void declararVar(char* s){
  if (buscar(s)!=1){
    agregar(s);
    generar("Declare", s, "Integer", "");
  }else{
    mensaje
    yyerror("Error semántico: identificador %s ya declarado", s); /* DEBERIA SER YYERROR MAYUSC */
  }
}
