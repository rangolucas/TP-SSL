#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "semantic.h"

char *diccionario[100];
int cantVar = 0;

int agregar(char* s){
  diccionario[cantVar] = s;
  /* Así compila hasta el primer temp.Esto solo apunta
  el puntero a la ubicacion del vector. Tal vez debería
  ser un doble puntero **diccionario y laburar con dos punteros. */
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
    // ERROR SEMANTICO
  }
}
