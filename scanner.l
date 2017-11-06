%{
#include <stdio.h>
#include <strings.h>
#include "parser.h"
void yyerror(const char*);
char mensaje[200];

%}
asignacion :=
letra [a-zA-Z]
digito [0-9]
otros [[:punct:]]{-}[();,+/*)-]
%option noinput
%option nounput
%option header-file="scanner.h"
%option outfile="scanner.c"
%option yylineno
%%
"+" return '+';
- return '-';
"/" return '/';
"*" return '*';
"(" return '(';
")" return ')';
; return ';';
, return ',';
"//".*  ;
programa return PROGRAMA;
variables return VARIABLES;
definir return DEFINIR;
codigo return CODIGO;
leer return LEER;
escribir return ESCRIBIR;
fin return FIN;
{letra}+({letra}|{digito})* {yylval =  strdup(yytext); return IDENTIFICADOR;}
{digito}+	{yylval =  strdup(yytext); return CTE;}
{asignacion}	return ASIGN;
{digito}+({letra}|{digito})*  {yylexerrs++; strcpy(mensaje, "Error léxico constante con sufijo inválido: "); strcat(mensaje, yytext); yyerror(mensaje);}
{otros}+  {yylexerrs++; strcpy(mensaje, "Error léxico: cadena desconocida: "); strcat(mensaje, yytext); yyerror(mensaje);}
{letra}+({letra}|{digito}|({otros}+))* {yylexerrs++; strcpy(mensaje, "Error léxico: identificador inválido: "); strcat(mensaje, yytext); yyerror(mensaje);}
[[:space:]] ;
