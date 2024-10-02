# Definimos el compilador
CC=gcc

# Opciones de compilación, por ejemplo, para la depuración y la generación de la información de depuración
CFLAGS=-Wall -g

# Nombre del archivo ejecutable que se generará
EXEC=interprete

# Todos los archivos fuente de tu proyecto
SRCS=main.c analizadorFlex.c sintactico.c tablaSimbolos.c errores.c abb.c

# Todos los archivos de cabecera
HEADERS=definiciones.h analizadorFlex.h tablaSimbolos.h sintactico.h errores.h abb.h

# Regla para el objetivo principal (el ejecutable)
$(EXEC): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) -lm

# Regla para limpiar los archivos generados durante la compilación
clean:
	rm -f $(EXEC) *.o

# Regla para ejecutar el programa (opcional)
run: $(EXEC)
	./$(EXEC)

