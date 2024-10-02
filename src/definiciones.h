#ifndef DEFINICIONES_H
#define DEFINICIONES_H



#define VARIABLE 300
#define FUNCION 301
#define CONSTANTE 302
#define COMANDO 303
#define ERROR_LEXICO 401



#define FIN_FICHERO 400

// TIPOELEM
typedef struct  {
    char *id;
    int tipo;
    union {
        float cantidad; //Valor de la variable
        double (*fnc)(); //Puntero a la función a ejecutar
        void (*cmd)(); //Puntero al comando a ejecutar
    }valor;
}tipoelem;

#endif // DEFINICIONES_H