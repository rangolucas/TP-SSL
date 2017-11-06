%code top{
#include <stdio.h>
#include "scanner.h"
#include "semantic.h"
#include "symbol.h"

}
%code provides{
void yyerror(const char *);
extern int yylexerrs;
}

%token IDENTIFICADOR CTE ASIGN ":=" PROGRAMA VARIABLES DEFINIR CODIGO LEER ESCRIBIR FIN
%define api.value.type {char*}
%define parse.error verbose
%defines "parser.h"
%output "parser.c"

%left '+' '-'
%left '*' '/'
%precedence NEG

%%
objetivo  : lenguaje FIN {terminar();}
lenguaje  : PROGRAMA {comenzar();} variables codigo {if (yylexerrs) YYABORT; }
variables : VARIABLES cuerpoVariables
codigo  : CODIGO cuerpoCodigo
cuerpoVariables : defVariable
  | cuerpoVariables defVariable
defVariable : DEFINIR id ';' {declararVar($2);}
  | error ';'
  ;
cuerpoCodigo : sentencia
  | cuerpoCodigo sentencia
sentencia : LEER '('queLeer')' ';'
  | id ASIGN operacion ';' { asignar($1, $3); }
  | ESCRIBIR '('operacion')' ';' {escribir_exp($3);}
  | error ';'
queLeer : id {leer_id($1);} /* [ -IMPORTANTE ] Hay que arreglar esta doble rutina semantica */
  | queLeer ',' id  {leer_id($3);}
operacion : CTE
  | id
  | '('operacion')'
  | '-'operacion %prec NEG {/*$$ = gen_infijo($2, 'N', NULL);*/} /* [ IMPORTANTE ] Este rompe todo con el void */
  | operacion '+' operacion {$$ = gen_infijo($1, $2, $3);}
  | operacion '-' operacion {$$ = gen_infijo($1, $2, $3);}
  | operacion '*' operacion  {$$ = gen_infijo($1, $2, $3);}
  | operacion '/' operacion  {$$ = gen_infijo($1, $2, $3);}
id : IDENTIFICADOR {$$ = $1;} /* [ IMPORTANTE ] Hay que arreglar el tema del id colgado */
