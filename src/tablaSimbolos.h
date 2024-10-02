#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H
#include "definiciones.h"

/**
 * Inicializa la tabla de símbolos con las constantes, funciones y comandos
 */
void inicializarTabla();
/**
 * Devuelve el tipo de un elemento de la tabla a partir de su id
 * @param id nombre del elemento
 */
int getTipo(char *id);
/**
 * Devuelve el valor de un elemento de la tabla a partir de su id
 * @param id nombre del elemento
 */
float getValor(char *id);
/**
 * Elimina la tabla de símbolos y libera la memoria
 */
void limpiarTabla();
/**
 * Imprime la tabla de símbolo
 */
void imprimirTabla();
/**
 * Inserta un elemento en la tabla
 * @param id id del elemento a insertar
 * @param valor valor del elemento, solo se usa en CONSTANTES y VARIABLES
 * @param func puntero a función cuando se inserte una función en la tabla
 * @param cmd puntero a función cuando se inserte un comando del intérprete en la tabla
 */
void insertarEnTabla(char* id, float valor, int tipo, double (*func)(), void(*cmd)());
/**
 * Actualiza el valor de una variable en la tabla
 * @param id nombre de la variable
 * @param valor nuevo valor de la variable
 */
void actualizarVariable(char *id, float valor);
/**
 * imprime el espacio de trabajo
 */
void imprimirWorkspace();
/**
 * Ejecuta una función almacenada en la tabla de símbolos
 * @param id nombre de la función
 * @param input input para la función
 */
double ejecutarFuncion(char *id, double input);
/**
 * Ejecuta el comando echo
 * @param id nombre del comando que será ECHO
 * @param input ON o OFF
 * @param estado entero que representa la variable de estado del ECHO
 */
void ejecutarEcho(char *id, char *input, int *estado);
/**
 * Ejecuta un comando de la tabla de símbolos
 * @param id nombre del comanod
 */
void ejecutarComando(char *id);
/**
 * Elimina las variables definidas por el usuario de la tabla de símbolos
 */
void limpiarWorkspace();
#endif // TABLA_SIMBOLOS_H

 
