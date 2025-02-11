# ------------------------------------------------------------------------------
# Nombre del ejecutable
# Este es el archivo final que se generará, ubicado en el directorio "bin"
TARGET = bin/main

# ------------------------------------------------------------------------------
# Compilador
# Se usará gcc para compilar el código en C
CC = gcc

# ------------------------------------------------------------------------------
# Flags de compilación
# -Wall y -Wextra: muestran todas las advertencias posibles para ayudarte a detectar problemas
# -Iinclude: indica al compilador que busque archivos de encabezado (.h) en el directorio "include"
CFLAGS = -Wall -Wextra -Iinclude

# ------------------------------------------------------------------------------
# Directorios
# SRC_DIR: Directorio donde se encuentran los archivos fuente (.c)
# OBJ_DIR: Directorio donde se guardarán los archivos objeto (.o) generados al compilar
SRC_DIR = src
OBJ_DIR = obj

# ------------------------------------------------------------------------------
# Obtener todos los archivos fuente (.c)
# La función wildcard busca todos los archivos que coinciden con el patrón especificado
# En este caso, busca todos los archivos con extensión .c dentro de SRC_DIR (ej: src/main.c, src/funciones.c)
SRCS = $(wildcard $(SRC_DIR)/*.c)

# ------------------------------------------------------------------------------
# Convertir los archivos fuente (.c) en archivos objeto (.o)
# La función patsubst realiza una sustitución de patrones en una lista de elementos.
#
# Sintaxis de patsubst:
#   $(patsubst <patrón>, <sustitución>, <lista>)
#
# En nuestro caso:
#   - Patrón a buscar: $(SRC_DIR)/%.c
#       Esto coincide con cualquier archivo .c en el directorio SRC_DIR.
#       El símbolo % es un comodín que representa la parte variable del nombre (ej: "main", "funciones", etc.)
#   - Sustitución: $(OBJ_DIR)/%.o
#       Reemplaza el directorio y la extensión, de modo que "src/main.c" se convierta en "obj/main.o"
#   - Lista: $(SRCS), que contiene todos los archivos .c encontrados en SRC_DIR.
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# ------------------------------------------------------------------------------
# Regla principal
# Al invocar "make" sin argumentos, se ejecuta la primera regla: "all".
# Aquí, "all" depende del TARGET, es decir, para tener el ejecutable, se deben generar
# todos los archivos que se requieren para él.
all: $(TARGET)

# ------------------------------------------------------------------------------
# Regla para compilar el ejecutable
# Esta regla indica que para generar $(TARGET) (bin/main) se necesitan todos los archivos objeto (OBJS)
$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

# ------------------------------------------------------------------------------
# Regla para compilar archivos objeto (.o) a partir de archivos fuente (.c)
# Esta es una regla de patrón que se aplica a cualquier archivo que cumpla con la forma:
#   $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#
# - El % actúa como un comodín que representa la parte variable del nombre del archivo (por ejemplo, "main" o "funciones")
# - Esto quiere decir que para compilar "src/main.c", se generará "obj/main.o", y así sucesivamente.
#
# La parte "| $(OBJ_DIR)" es una dependencia de orden (order-only dependency)
# que asegura que el directorio OBJ_DIR exista antes de compilar cualquier archivo objeto.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------------------------------
# Regla para crear el directorio de objetos si no existe
# Esto se usa para asegurarse de que el directorio OBJ_DIR esté presente antes de crear los .o
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ------------------------------------------------------------------------------
# Regla para limpiar los archivos generados
# "make clean" eliminará los archivos objeto y el ejecutable, permitiendo una compilación limpia.
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# ------------------------------------------------------------------------------
# Declarar que "all" y "clean" son objetivos ficticios (phony)
# Esto evita conflictos si existen archivos o directorios con esos nombres.
.PHONY: all clean
