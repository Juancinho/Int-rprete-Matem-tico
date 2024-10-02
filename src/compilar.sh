#!/bin/bash

# Compila el analizador léxico con flex
flex -o analizadorFlex.c analizadorFlex.l

# Verifica si flex se ejecutó exitosamente
if [ $? -eq 0 ]; then
    echo "Flex ejecutado con éxito, ahora ejecutando Bison..."
    
    # Ejecuta Bison para generar el analizador sintáctico
    bison -d -o sintactico.c sintactico.y
    
    # Verifica si bison se ejecutó exitosamente
    if [ $? -eq 0 ]; then
        echo "Bison ejecutado con éxito, ahora ejecutando make..."
        # Ejecuta make para compilar el proyecto
        make
    else
        echo "Bison falló, abortando..."
    fi
else
    echo "Flex falló, abortando..."
fi

