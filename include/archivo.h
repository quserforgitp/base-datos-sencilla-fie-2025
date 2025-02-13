#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_PREDETERMINADO_ARCHIVO "nombres.db"

/**
 * @brief Verifica si un archivo existe.
 * 
 * @param nombre_archivo Nombre del archivo a verificar.
 * @return true si el archivo existe, false si no.
 */
bool existe_el_archivo(const char *nombre_archivo);

/**
 * @brief Crea un archivo si no existe.
 * 
 * @param nombre_archivo Nombre del archivo a crear.
 * @return true si el archivo se creó correctamente, false si hubo un error.
 */
bool crea_el_archivo(const char *nombre_archivo);

/**
 * @brief Verifica si un archivo no se pudo abrir.
 * 
 * @param archivo Puntero al archivo.
 * @return true si el archivo no se pudo abrir, false si se abrió correctamente.
 */
bool no_se_pudo_abrir_archivo(FILE *archivo);

/**
 * @brief Inicializa un archivo de IDs, escribiendo un 0 en él.
 * 
 * @param nombre_archivo Nombre del archivo donde se guardarán los IDs.
 */
void inicializa_el_archivo_de_ids(const char *nombre_archivo);

#endif // ARCHIVO_H
