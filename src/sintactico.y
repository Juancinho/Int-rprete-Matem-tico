%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tablaSimbolos.h"
#include "definiciones.h"
#include "analizadorFlex.h"
#include <stdbool.h>

int echo_enabled = 0;


extern int yylex();
void yyerror(char *s);
%}

%union {
    double num;
    char *id;
}

%token <id> ID ARCHIVO
%token  MAYOR_IGUAL MENOR_IGUAL IGUAL_IGUAL POTENCIA POR_IGUAL
%token <num> FLOAT
%token WORKSPACE
%token ECHOO
%token HELP
%token QUIT
%token CLEAR
%token LOAD

%token '(' ')'


%right '='
%left '<' '>' IGUAL_IGUAL MENOR_IGUAL MAYOR_IGUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left NEGATIVE
%right '^'


%type <num> exp
%type <num> operaciones
%type <num> asignaciones
%type <num> funciones
%type <num> comparaciones
%type <num> carga


%%
input:
	| input line
;

line:
    '\n'    { if (echo_enabled) printf("> "); }
    | exp ';' '\n' { printf("> %f\n> ", $1); }
    | exp '\n' { if (echo_enabled){ 
                    printf("> %f\n> ", $1);
                    } else{
                        printf("> \n> ");
                    } }
    | HELP '\n' { ejecutarComando("HELP"); printf("> "); }
    | WORKSPACE '\n' {ejecutarComando("WORKSPACE");printf("> ");}
    | CLEAR '\n'{ejecutarComando("CLEAR");printf("Borrando workspace...\n> ");}
    | ECHOO '(' ID ')' {ejecutarEcho("ECHO",$3,&echo_enabled);printf("> ECHO %s\n",$3); free($3);}
    | QUIT '\n' { printf("Saliendo del intérprete...\n");cerrar();YYACCEPT; }
    | error { yyclearin; yyerrok; }
    ;



exp:	FLOAT	{$$ = $1;}
	| '-' exp	{$$ = -$2;}
    | ID {  if(getTipo($1) !=0){ 
                $$=getValor($1);
                free($1);
            }else{
                yyerror("No existe ningún identificador con ese nombre");
                free($1);
            }
            }
    | '(' exp ')'  {$$ = $2;}  // Regla para manejar paréntesis
    | asignaciones
    | operaciones
    | comparaciones
    | funciones
    | carga
	
;


asignaciones: ID '=' exp {  if(getTipo($1)==CONSTANTE){
                                yyerror("No puedes asignar un valor a una constante matemática");
                                free($1);
                            }
                            else{
                                if(getTipo($1)==0){
                                    insertarEnTabla($1,$3,VARIABLE,NULL,NULL); 
                                    $$=$3;
                                    

                                }else{
                                    actualizarVariable($1,$3);
                                    $$=$3;
                                }
                                free($1);
                                
                                }
                        
                        }
;



operaciones:    exp '+' exp {$$ = $1 + $3;}
            | exp '-' exp {$$ = $1 - $3;}
            | exp '*' exp {$$ = $1 * $3;}
            | exp '/' exp { if($3 != 0){
                                $$ = $1 / $3;
                                } else {
                                    yyerror("Divisón entre 0");
                                }
                            }
            | exp '^' exp {$$ = pow($1,$3);}
            | exp '%' exp {$$ = (int)$1 % (int)$3;}
;



funciones: ID '(' exp ')'{  if(getTipo($1)==FUNCION){
                                $$ = ejecutarFuncion($1,$3);
                            }else{
                                printf("No existe la funcion\n");
                            }
                            free($1);}

comparaciones: exp '>' exp{ if($1 > $3){
                                printf("TRUE\n");
                            }else{
                                printf("FALSE\n");
                            }}
            | exp '<' exp{  if($1 < $3){
                            printf("TRUE\n");
                            }else{
                                printf("FALSE\n");
                            }}
            | exp MAYOR_IGUAL exp{ if($1 >= $3){
                                printf("TRUE\n");
                            }else{
                                printf("FALSE\n");
                            }}
            | exp MENOR_IGUAL exp{ if($1 <= $3){
                                printf("TRUE\n");
                            }else{
                                printf("FALSE\n");
                            }}
            | exp IGUAL_IGUAL exp{ if($1 == $3){
                                printf("TRUE\n");
                            }else{
                                printf("FALSE\n");
                            }}

;

carga: LOAD ARCHIVO {abrirArchivo($2); free($2);}
;

%%


void yyerror(char *s) {
    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr, "Error de sintaxis en la línea %d\n> ", yylineno);
    } else {
        fprintf(stderr, "%s en la línea %d\n", s, yylineno);
    }
}






