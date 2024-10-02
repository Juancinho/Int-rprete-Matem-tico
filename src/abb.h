#ifndef ABB_H
#define ABB_H
#include "definiciones.h"

/**
 * Tipo de dato abstracto para arbol binario con clave de
 * ordenacion y elemento de celda.
 */

typedef char * tipoclave; // tipo de clave

typedef struct celda * abb;//tipo opaco

//FUNCIONES DE CREACIÓN Y DESTRUCCIÓN DEL ÁRBOL
/**
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear(abb *A);

/**
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir(abb *A);

//FUNCIONES DE INFORMACIÓN
/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned es_vacio(abb A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abb izq(abb A);
/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abb der(abb A);
/**
 * Recupera la informacion de la celda de la raiz del arbol
 * @param A
 * @param E Puntero al nodo que apuntara a la informacion
 */
void leer(abb A, tipoelem *E);

/**
 * Comprueba si el elemento <E> existe en el arbol <A>
 * @param A
 * @param E
 */
unsigned es_miembro(abb A, tipoelem E);

/**
 * Busca un nodo con clave <cl> en el arbol y, si existe
 * modifica el puntero <nodo> para que lo apunte.
 * @param A Arbol binario en el que se busca el nodo.
 * @param cl Clave que se buscara.
 * @param nodo Puntero a un tipoelem.
 */
void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo);

/**
 * Buscar el tipo de un nodo con id id en el arbol y, si existe
 * devuelve el tipo
 * @param A Arbol binario en el que se busca el nodo.
 * @param id Id del elemento a buscar.
 */

int buscarTipoPorID(abb A, const char* id);

/**
 * Buscar el valor de un nodo con id id en el arbol y, si existe
 * devuelve el tipo
 * @param A Arbol binario en el que se busca el nodo.
 * @param id Id del elemento a buscar.
 */

float buscarValorPorID(abb A, const char* id);

//FUNCIONES DE MODIFICACIÓN
/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * del que toma su clave. Esta clave no debe existir en
 * el arbol.
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo.
 */
void insertar(abb *A, tipoelem E);
/**
 * Suprime el nodo del arbol <A>
 * @param A
 * @param E
 */
void suprimir(abb *A,tipoelem E);
/**
 * Busca el nodo con clave la del nodo y lo modifica.
 * @param A
 * @param nodo
 */
void modificar(abb A, tipoelem nodo);

/**
 * Imprime las variables definidas por el usuario almacenadas en el árbol
 * @param A arbol binario
 */
void _imprimirWorkspace(abb A);

/**
 * Busca la función con el nombre id en la tabla y la ejecuta con el input
 * @param A arbol binario
 * @param id nombre de la función
 * @param input parámetro que se le pasa a la función
 */
double _ejecutarFuncion(abb *A, char *id, float input);

/**
 * Ejecuta el comando echo con el parámetro ON/OFF
 * @param A arbol binario
 * @param id nombre del comando
 * @param input parámetro que se le pasa ON/OFF
 * @param estado variable global definida en el archivo de bison que funciona como variable de estado para mostrar o no la salida de los resultados por pantalla.
 */
void _ejecutarEcho(abb *A,char *id, char *input, int *estado);
/**
 * Busca el comando con el nombre id en la tabla y lo ejecuta
 * @param A arbol binario
 * @param id nombre del comando
 */
void _ejecutarComando(abb *A, char *id);
/**
 * Borra las variables del árbol
 * @param A arbol binario
 */
void eliminarVariables(abb *A);

#endif //ABB_H