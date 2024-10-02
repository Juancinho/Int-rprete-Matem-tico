#include "abb.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct celda {
    tipoelem info;
    struct celda *izq, *der;
};


/*Extraer la clave de una celda */
tipoclave _clave_elem(tipoelem *E) {
    return E->id;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    if(strcmp(cl1,cl2) == 0){
        return 0;
    }else if(strcmp(cl1,cl2) > 0){
        return 1;
    }else{
        return -1;
    }
}

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}

void destruir(abb *A) {
    if (*A != NULL) {
        destruir(&(*A)->izq);
        destruir(&(*A)->der);
        free((*A)->info.id);
        
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void leer(abb A, tipoelem *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, tipoelem E) {
    return _comparar_claves(cl, _clave_elem(&E));
}
//Función privada para informar si una clave está en el árbol

unsigned _es_miembro_clave(abb A, tipoclave cl) {
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { //cl == A->info
        return 1;
    }
    if (comp > 0) { //cl > A->info
        return _es_miembro_clave(der(A), cl);
    }
    //cl < A->info
    return _es_miembro_clave(izq(A), cl);
}

//Funciones públicas

unsigned es_miembro(abb A, tipoelem E) {
    return _es_miembro_clave(A, _clave_elem(&E));
}

void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        *nodo = A->info;
    } else if (comp < 0) { // cl < A->info
        buscar_nodo(A->izq, cl, nodo);
    } else { // cl > A->info
        buscar_nodo(A->der, cl, nodo);
    }
}


int buscarTipoPorID(abb A, const char* id) {
    if (es_vacio(A)) {
        return 0;  // El elemento no se encontró
    }

    int comp = strcmp(id, A->info.id);
    if (comp == 0) {  // El identificador coincide
        return A->info.tipo;
    } else if (comp < 0) {
        return buscarTipoPorID(izq(A), id);  // Buscar en el subárbol izquierdo
    } else {
        return buscarTipoPorID(der(A), id);  // Buscar en el subárbol derecho
    }
}

float buscarValorPorID(abb A, const char* id) {
    if (es_vacio(A)) {
        return 0;  // El elemento no se encontró
    }

    int comp = strcmp(id, A->info.id);
    if (comp == 0) {  // El identificador coincide
        return A->info.valor.cantidad;
    } else if (comp < 0) {
        return buscarValorPorID(izq(A), id);  // Buscar en el subárbol izquierdo
    } else {
        return buscarValorPorID(der(A), id);  // Buscar en el subárbol derecho
    }
}




//OPERACIONES DE MODIFICACIÓN

/* Funcion recursiva para insertar un nuevo nodo 
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertar(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info = E;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp > 0) {
        insertar(&(*A)->der, E);
    } else {
        insertar(&(*A)->izq, E);
    }
}
/* Funcion privada que devuelve mínimo de subárbol dcho */
tipoelem _suprimir_min(abb * A) {//Se devuelve el elemento más a la izquierda
    abb aux;
    tipoelem ele;
    if (es_vacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}

/* Funcion que permite eliminar un nodo del arbol */
void suprimir(abb *A, tipoelem E) {
    abb aux;
    if (es_vacio(*A)) {
        return;
    }

    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp < 0) { //if (E < (*A)->info) {
        suprimir(&(*A)->izq, E);
    } else if (comp > 0) { //(E > (*A)->info) {
        suprimir(&(*A)->der, E);
    } else if (es_vacio((*A)->izq) && es_vacio((*A)->der)) {
        free(*A);
        *A = NULL;
    } else if (es_vacio((*A)->izq)) { // pero no es vacio derecha
        aux = *A;
        *A = (*A)->der;
        free(aux);
    } else if (es_vacio((*A)->der)) { //pero no es vacio izquierda
        aux = *A;
        *A = (*A)->izq;
        free(aux);
    } else { //ni derecha ni izquierda esta vacio, busco mínimo subárbol derecho
        //pues en su sitio voy a poner el mínimo del subárbol derecho
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}

/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.*/
void _modificar(abb A, tipoclave cl, tipoelem nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);
    if (comp == 0) {
        A->info = nodo;
    } else if (comp < 0) {
        _modificar(A->izq, cl, nodo);
    } else {
        _modificar(A->der, cl, nodo);
    }
}


/* Permite modificar el nodo extrayendo del mismo la clave */
void modificar(abb A, tipoelem nodo) {
    tipoclave cl = _clave_elem(&nodo);
    _modificar(A, cl, nodo);
}

// Imprimer las variables definidas por el usuario
void _imprimirWorkspace(abb A){
    tipoelem e;
    if(!es_vacio(A)){
        _imprimirWorkspace(izq(A));
        leer(A,&e);
        if(e.tipo==VARIABLE){
            printf("%s -> %f\n",e.id,e.valor.cantidad);

        }
        
        _imprimirWorkspace(der(A));
    }

}


//Busca la función con nombre id en el árbol y la ejecuta con el input 
double _ejecutarFuncion(abb *A, char *id, float input){
    if(!es_vacio(*A)){
        if(strcmp(id, (*A)->info.id) == 0){
            return (*A)->info.valor.fnc(input);
        } else if(strcmp(id, (*A)->info.id) < 0){
            return _ejecutarFuncion(&(*A)->izq, id, input);
        } else {
            return _ejecutarFuncion(&(*A)->der, id, input);
        }
    }

    return 0;
}

//Ejecuta el comando con nombre id
void _ejecutarComando(abb *A, char *id){
    if(!es_vacio(*A)){
        if(strcmp(id, (*A)->info.id) == 0){
            return (*A)->info.valor.cmd();
        } else if(strcmp(id, (*A)->info.id) < 0){
            return _ejecutarComando(&(*A)->izq, id);
        } else {
            return _ejecutarComando(&(*A)->der, id);
        }
    }

}

//Ejecuta el comando echo, el parámetro input es ON/OFF y estado es una variable global que está en el archivo bison
void _ejecutarEcho(abb *A,char *id, char *input, int *estado){
    if(!es_vacio(*A)){
        if(strcmp(id, (*A)->info.id) == 0){
            return (*A)->info.valor.cmd(input,estado);
        } else if(strcmp(id, (*A)->info.id) < 0){
            return _ejecutarEcho(&(*A)->izq, id, input, estado);
        } else {
            return _ejecutarEcho(&(*A)->der, id, input, estado);
        }
    }


}


//Función que se ejecuta al llamar a CLEAR() y que elimina del árbol las variables definidas por el usuario
void eliminarVariables(abb *A) {
    if (!es_vacio(*A)) {
        tipoelem elemento;
        leer(*A, &elemento);
        eliminarVariables(&((*A)->izq));  // Recorrer subárbol izquierdo
        eliminarVariables(&((*A)->der));  // Recorrer subárbol derecho

        if (elemento.tipo == VARIABLE) {
            suprimir(A, elemento);
            
        }
    }
    
}

