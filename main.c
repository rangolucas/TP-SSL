/*
TP4 - 2017
Grupo 12

Integrantes: (APELLIDO, Nombre - Legajo)

CALVIELLO, Martín  160619-0
MARANZANA, Ramiro  158908-8
RANGO, Lucas       160226-3
RODRIGUEZ, Melisa  160184-2
*/
#include <stdio.h>
#include "scanner.h"
#include "parser.h"

void yyerror(const char *);

int yylexerrs = 0;
int yynerrs = 0;

int main() {
  switch ( yyparse() ) {
    case 0:
      printf("Compilación terminada con éxito\n");
      printf("Errores sintácticos: %d - Errores léxicos: %d\n", yynerrs, yylexerrs);
      return 0;
    case 1:
      printf("Errores de compilación\n");
      printf("Errores sintácticos: %d - Errores léxicos: %d\n", yynerrs, yylexerrs);
      return 1;
    case 2:
      printf("Memoria insuficiente\n"); return 2;
  }
  return 0;
}

void yyerror(const char *error){
	printf("línea #%d: %s\n", yylineno, error);
	return;
}
