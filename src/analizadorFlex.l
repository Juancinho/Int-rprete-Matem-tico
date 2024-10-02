%{
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "sintactico.h"

void abrirArchivo(char *nombreArchivo);
void cerrar();
tipoelem elementoActual; // Variable global para almacenar el token actual
%}

/*OPCIONES*/
%option noyywrap 
%option nounput
%option noinput


/*ESPACIOS*/
SALTOLINEA       \n
ESPACIO       [\t\r]
INDENTACION   {ESPACIO}+
PUNTOCOMA     ;

LETRA     [a-zA-Z]
/*NÚMEROS ENTEROS*/
DIGIT        [0-9]

/*NÚMEROS FLOTANTES*/   
DIGITPART     {DIGIT}(\_?{DIGIT})*
FRACTION      \.{DIGITPART}*
EXPONENT      (e|E)[+-]?{DIGITPART}
POINTFLOAT    {DIGITPART}?{FRACTION}
EXPONENTFLOAT ({POINTFLOAT}{EXPONENT}|{DIGITPART}{EXPONENT})
FLOAT         ({DIGIT}+|{POINTFLOAT}|{EXPONENTFLOAT})


/*OPERADORES Y DELIMITADORES*/
OPERADOR    (\+|\-|\*|\/|\%|\@|\<|\>|\&|\||\^|\~|\:|\<|\>|\(|\)|\[|\]|\{|\}|\,|\.|\;|\=)


MAYOR_IGUAL (\>\=)
MENOR_IGUAL (\<\=)
IGUAL_IGUAL (\=\=)
POTENCIA    (\*\*)
POR_IGUAL   (\*\=)


/*IDENTIFICADORES */
ID ({LETRA}|\_)({LETRA}|{DIGIT}|\_)*

ARCHIVO [a-zA-Z0-9_]+\.[a-zA-Z0-9]+




%x LECTURA


%%

"WORKSPACE()" {return WORKSPACE;}
"ECHO"      {return ECHOO;}
"HELP()"    { return HELP; }
"QUIT()"    {return QUIT;}
"CLEAR()"   {return CLEAR;}

"("         { return '('; }
")"         { return ')'; }

"LOAD"  {
        BEGIN(LECTURA);
        return LOAD;
        }

<LECTURA>{ARCHIVO}  {yylval.id = strdup(yytext); 
                    BEGIN(INITIAL); 
                    return ARCHIVO;}


{INDENTACION}   {/*Ignorar los espacios*/}
{SALTOLINEA}    { return ((int) *yytext);}
{OPERADOR}      { return ((int) *yytext);}
{FLOAT}         { yylval.num = atof(yytext);return FLOAT;}
{MAYOR_IGUAL}   { return MAYOR_IGUAL;}
{MENOR_IGUAL}   { return MENOR_IGUAL;}
{IGUAL_IGUAL}   { return IGUAL_IGUAL;}
{POTENCIA}      { return POTENCIA;}
{POR_IGUAL}     { return POR_IGUAL;}
{ID}            { yylval.id=strdup(yytext); return ID;}

.               {return -2;}
<<EOF>>      {cerrar();yyrestart(stdin);}
%%



void abrirArchivo(char *nombreArchivo) {
    
    if((yyin = fopen(nombreArchivo, "r")) == NULL) {
        perror("Error al abrir el archivo");
        yyin = stdin;
    }else{
        printf("Script cargado correctamente\n");

    }
    
    
}
void cerrar() {
    
    fclose(yyin);
    
}

