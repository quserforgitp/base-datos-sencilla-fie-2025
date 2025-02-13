#include "archivo.h"

/**
 * Verifica si un archivo existe intentando abrirlo en modo lectura.
 */
bool existe_el_archivo(const char *nombre_archivo) {
    return fopen(nombre_archivo, "r") != NULL;
}

/**
 * Intenta crear un archivo en modo "a" (append).
 * Si no puede crearlo, imprime un mensaje de error.
 */
bool crea_el_archivo(const char *nombre_archivo) {
    if (fopen(nombre_archivo, "a") == NULL) {
        printf("No pudo crearse el archivo \"%s\"\n", nombre_archivo);
        return false;
    }
    printf("Se creó el archivo \"%s\"\n", nombre_archivo);
    return true;
}

/**
 * Retorna true si el puntero al archivo es NULL, lo que indica que no se pudo abrir.
 */
bool no_se_pudo_abrir_archivo(FILE *archivo) {
    return archivo == NULL;
}

/**
 * Abre el archivo en modo "w" (escritura) para inicializarlo con el ID 0.
 * Si el archivo no se puede abrir, termina el programa con `exit(1)`.
 */
void inicializa_el_archivo_de_ids(const char *nombre_archivo) {
    FILE *archivo_ids = fopen(nombre_archivo, "w");

    if (no_se_pudo_abrir_archivo(archivo_ids)) {
        printf("No se pudo abrir el archivo \"%s\"\n", nombre_archivo);
        exit(1);
    }

    // Escribimos un 0 en el archivo como valor inicial de los IDs.
    fprintf(archivo_ids, "%d", 0);
    fclose(archivo_ids);
}

