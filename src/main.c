#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablaSimbolos.h"
#include "sintactico.h"
#include "analizadorFlex.h"

int main(int argc, char *argv[])
{

    // Inicializar tabla de símbolos y mostrarla por pantalla
    inicializarTabla();
    printf("> ");
    // Iniciar analizador sintáctico
    yyparse();
    // Borrar la tabla de símbolos
    yylex_destroy();
    limpiarTabla();

    return 0;
}
