#ifndef UTILES_H
#define UTILES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//
// =============================================================
//                     FUNCIONES GENERALES
// =============================================================
//

/**
 * @brief Imprime el manual de uso del programa.
 *
 * Este manual explica cómo ejecutar el programa y el uso opcional
 * de un argumento para especificar el nombre del archivo de base de datos.
 */
void imprime_manual_de_uso();


//
// =============================================================
//                UTILIDADES PARA ENTRADA POR TECLADO
// =============================================================
//

/**
 * @brief Obtiene una entrada de texto desde el teclado sin el salto de línea final.
 *
 * La función reserva dinámicamente memoria para almacenar la cadena introducida.
 * Si el texto ingresado supera el tamaño del búfer, se limpia el resto de la entrada.
 * El retorno debe liberarse con `free()` al finalizar su uso.
 *
 * @param tamanio_buffer_entrada Tamaño máximo de caracteres a leer (incluye '\0').
 * @return Puntero a la cadena leída o NULL si ocurre un error.
 */
char *obtiene_entrada_por_teclado_sin_salto_linea( int tamanio_buffer_entrada );

/**
 * @brief Limpia el búfer de entrada estándar (stdin).
 *
 * Se utiliza para descartar cualquier carácter remanente en stdin,
 * como cuando el usuario introduce más caracteres de los esperados.
 */
void limpia_stdin();

/**
 * @brief Verifica si una cadena contiene un salto de línea.
 *
 * @param cadena Cadena de texto a analizar.
 * @return true si contiene '\n', false en caso contrario.
 */
bool existe_salto_de_linea_en_cadena( char cadena[] );

/**
 * @brief Elimina el salto de línea de una cadena si lo contiene.
 *
 * Reemplaza el primer '\n' encontrado en la cadena por el carácter nulo '\0'.
 *
 * @param cadena Cadena de texto a modificar.
 */
void quita_salto_de_linea_de_cadena( char cadena[] );

void limpia_pantalla();

#endif   // UTILES_H
