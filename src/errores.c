#include <stdlib.h>
#include <stdio.h>

void error(int opcion);
void error(int opcion){
    switch (opcion)
    {
    case 1:
        printf("Error: tamaño de lexema excede el tamaño de buffer\n");
        break;
    
    case 2:
        printf("Error: no se encuentra el archivo especificidado\n");
        exit(EXIT_FAILURE);
        break;
    case 3:
        printf("Error: el lexema no se corresponde con ningún componente léxico de Python\n");
        break;;
    case 4:
        printf("Error: debes pasar el nombre de archivo como argumento\n");
        exit(EXIT_FAILURE);
        break;
    case 5:
        printf("Error: no se ha podido reservar la memoria correctamente\n");
        exit(EXIT_FAILURE);
    
    default:
        break;
    }
}