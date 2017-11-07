#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

enum tipo{ID, CONST};

void comenzar(void);
void terminar();
void generar(char*, char*, char*, char*);
//void extraer(REG_EXPRESION);
void asignar (char*,char*);
void leer_id(char*);
void escribir_exp (char*);
int procesar(char*);
char *gen_infijo(char*, char, char*);

#endif // SEMANTIC_H_INCLUDED
