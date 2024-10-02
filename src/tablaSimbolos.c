#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "abb.h"
#include "definiciones.h"
#include "constantes.h"

abb tablaSimbolos;

void insertarEnTabla(char *id, float valor, int tipo, double (*func)(), void (*cmd)());
void inicializarTabla();
void limpiarTabla();
void imprimirTabla();
void buscarElemento(tipoelem *e);
void actualizarVariable(char *id, float valor);
void _impresionRecursivaArbol(abb A);
void imprimirWorkspace();
void echo(const char *input, int *estado);
void limpiarWorkspace();
void ayuda();

void inicializarTabla()
{
    crear(&tablaSimbolos); // Creamos el abb que constituirá nuestra tabla de símbolos

    //Metemos las constantes en la tabla
    insertarEnTabla("E", E, CONSTANTE, NULL, NULL);
    insertarEnTabla("PI", PI, CONSTANTE, NULL, NULL);
    insertarEnTabla("PHI", PHI, CONSTANTE, NULL, NULL);
    //Metemos las funciones de math.h en la tabla
    insertarEnTabla("sin", 0, FUNCION, sin, NULL); //el 0 es un valor arbitrario que se coloca porque es necesario introducir un valor numérico en la función insertarTabla
    insertarEnTabla("cos", 0, FUNCION, cos, NULL);
    insertarEnTabla("acos", 0, FUNCION, acos, NULL);
    insertarEnTabla("asin", 0, FUNCION, asin, NULL);
    insertarEnTabla("atan", 0, FUNCION, atan, NULL);
    insertarEnTabla("atan2", 0, FUNCION, atan2, NULL);
    insertarEnTabla("cosh", 0, FUNCION, cosh, NULL);
    insertarEnTabla("sinh", 0, FUNCION, sinh, NULL);
    insertarEnTabla("tanh", 0, FUNCION, tanh, NULL);
    insertarEnTabla("exp", 0, FUNCION, exp, NULL);
    insertarEnTabla("log", 0, FUNCION, log, NULL);
    insertarEnTabla("log10", 0, FUNCION, log10, NULL);
    insertarEnTabla("sqrt", 0, FUNCION, sqrt, NULL);
    insertarEnTabla("ceil", 0, FUNCION, ceil, NULL);
    insertarEnTabla("fabs", 0, FUNCION, fabs, NULL);
    insertarEnTabla("pow", 0, FUNCION, pow, NULL);
    // Insertamos los comandos del intérprete en la tabla
    insertarEnTabla("WORKSPACE", 0, COMANDO, NULL, imprimirWorkspace);
    insertarEnTabla("CLEAR", 0, COMANDO, NULL, limpiarWorkspace);
    insertarEnTabla("ECHO", 0, COMANDO, NULL, echo);
    insertarEnTabla("HELP", 0, COMANDO, NULL, ayuda);
}

double ejecutarFuncion(char *id, double input)
{
    return _ejecutarFuncion(&tablaSimbolos, id, input);
}

void ejecutarComando(char *id)
{
    return _ejecutarComando(&tablaSimbolos, id);
}

void ejecutarEcho(char *id, char *input, int *estado)
{
    return _ejecutarEcho(&tablaSimbolos, id, input, estado);
}
//Función para insertar elementos de la tabla: CONSTANTES, VARIABLES, FUNCIONES O COMANDOS
void insertarEnTabla(char *id, float valor, int tipo, double (*func)(), void (*cmd)())
{
    tipoelem e;
    int tam = strlen(id) + 1;
    e.id = (char *)malloc(tam);
    strcpy(e.id, id);
    e.tipo = tipo;

    if (tipo == FUNCION && func != NULL) //Si es una función se le asigna la función pasada por parámetro en el campo fnc
    {
        e.valor.fnc = func;
    }
    else if (tipo == COMANDO && cmd != NULL) //Si el tipo es comando, se le asigna la función pasada por parámetro en el campo cmd
    {
        e.valor.cmd = cmd;
    }
    else //En otro caso se trata de una variable o una constante
    {
        e.valor.cantidad = (float)valor; // Asignamos el valor convertido a float
    }

    insertar(&tablaSimbolos, e); // Insertamos el elemento en el árbol binario que es la tabla
}

//Funcion para cambiar el valor de una variable
void actualizarVariable(char *id, float valor)
{
    tipoelem e; //Creamos un elemento
    int tam = strlen(id) + 1;
    e.id = (char *)malloc(tam);
    strcpy(e.id, id); //Ponemos el id que se pasa por argumento
    e.tipo = VARIABLE; //Establecemos el tipo en VARIABLE
    e.valor.cantidad = valor; //Establecemos el valor que se pasa por argumento
    modificar(tablaSimbolos, e); //Modificamos el elemento existente por este
    
}

//Función que devuelve el tipo de un elemento de la tabla a partir de su id
int getTipo(char *id)
{
    return buscarTipoPorID(tablaSimbolos, id);
}
//Función que devuelve el valor de un elemento de la tabla a partir de su id
float getValor(char *id)
{
    return buscarValorPorID(tablaSimbolos, id);
}

void limpiarTabla()
{
    destruir(&tablaSimbolos);
}

void _impresionRecursivaArbol(abb A)
{
    tipoelem e;
    if (!es_vacio(A))
    {
        _impresionRecursivaArbol(izq(A));
        leer(A, &e);
        printf("%s -> %d\n", e.id, e.tipo); // Modificaremos esto para mostrar el Workspace
        _impresionRecursivaArbol(der(A));
    }
}
//Función para imprimir el espacio de trabajo
void imprimirWorkspace()
{
    _imprimirWorkspace(tablaSimbolos);
}
//Función para el ECHO
void echo(const char *input, int *estado)
{
    if (strcmp(input, "ON") == 0) //Copiamos el input del usuario ON o OFF
    {
        *estado = 1; //Si es ON ponemos la variable de estado en 1
    }
    else if (strcmp(input, "OFF") == 0)
    {
        *estado = 0; //Si es OFF ponemos la variable de estado a 0
    }
    else
    {
        printf("Error: entrada inválida. Use 'ON' o 'OFF'.\n");
    }
}
//Función para borrar las variables de la tabla de símbolos
void limpiarWorkspace()
{
    eliminarVariables(&tablaSimbolos);
}

void imprimirTabla()
{
    printf("-----------INICIO TABLA DE SIMBOLOS -----------\n");
    _impresionRecursivaArbol(tablaSimbolos);
    printf("-----------FIN TABLA DE SIMBOLOS -----------\n");
}

//Función de ayuda
void ayuda() {
    printf("\nAyuda del Intérprete de Expresiones Matemáticas:\n");
    printf("==============================================================\n\n");

    printf("EXPRESIONES BÁSICAS:\n");
    printf("  - Operadores: Utiliza +, -, *, /, ^, y %% para operaciones.\n");
    printf("  - Paréntesis: Usa paréntesis () para agrupar operaciones y definir el orden.\n\n");

    printf("ASIGNACIONES:\n");
    printf("  - Formato: variable = expresión; Ejemplo: x = 5 * (3 + 2);\n\n");

    printf("FUNCIONES MATEMÁTICAS:\n");
    printf("  - Formato: nombre_función(argumento); Ejemplos: sin(0.5), log(10);\n\n");

    printf("COMPARACIONES:\n");
    printf("  - Operadores: >, <, >=, <=, ==. Ejemplo: 5 > 3;\n\n");

    printf("COMANDOS ESPECIALES:\n");
    printf("  - WORKSPACE(): Muestra todas las variables y funciones definidas.\n");
    printf("  - CLEAR(): Limpia el espacio de trabajo, eliminando todas las variables.\n");
    printf("  - ECHO(ON/OFF): Activa o desactiva la salida automática de los resultados de las expresiones.\n");
    printf("  - HELP(): Muestra esta pantalla de ayuda.\n");
    printf("  - QUIT(): Sale del intérprete.\n\n");

    printf("CARGA DE ARCHIVOS:\n");
    printf("  - LOAD 'nombre_de_archivo': Ejecuta comandos desde un archivo.\n\n");

    printf("NOTAS ADICIONALES:\n");
    printf("  - Finaliza todas las instrucciones y comandos con un punto y coma (;) para ver el resultado.\n");

    printf("==============================================================\n");
}
