/**
 * @file validacion.h
 * @brief Declaraciones de funciones para validación y manipulación de cadenas de
 * caracteres en C y UTF-8.
 */

#ifndef VALIDACION_H
#define VALIDACION_H

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Verifica si una cadena representa un número entero válido.
 * @param cadena Cadena a evaluar.
 * @return true si es un número válido, false en caso contrario.
 */
bool es_un_numero( const char cadena[] );

/**
 * @brief Convierte una cadena numérica a un número entero.
 * @param cadena Cadena que representa un número.
 * @return Valor entero resultante.
 */
int convierte_a_numero( const char cadena[] );

/**
 * @brief Verifica si una cadena representa una matrícula válida.
 * @param cadena Cadena a validar.
 * @return true si el formato es válido, false en caso contrario.
 */
bool el_formato_de_matricula_es_valido( const char cadena[] );

/**
 * @brief Verifica si un nombre tiene un formato válido (solo letras y espacios).
 * @param cadena Cadena que representa el nombre.
 * @return true si el formato es válido, false en caso contrario.
 */
bool el_formato_de_nombre_es_valido( const char cadena[] );

/**
 * @brief Elimina espacios en blanco al inicio y final de una cadena.
 * @param cadena Cadena original.
 * @return Cadena nueva sin espacios sobrantes.
 */
char *remueve_espacios_sobrantes_principio_y_final( char cadena[] );

/**
 * @brief Obtiene el índice del primer carácter no blanco (' ' o '\t').
 * @param cadena Cadena a evaluar.
 * @return Índice del primer carácter válido o -1 si no hay ninguno.
 */
int obtiene_indice_del_primer_caracter_no_blank( const char cadena[] );

/**
 * @brief Obtiene el índice del último carácter no blanco (' ' o '\t').
 * @param cadena Cadena a evaluar.
 * @return Índice del último carácter válido o -1 si no hay ninguno.
 */
int obtiene_indice_del_ultimo_caracter_no_blank( const char cadena[] );

/**
 * @brief Rellena una cadena con terminadores nulos ('\0').
 * @param cadena Cadena a limpiar.
 */
void rellena_cadena_con_null_terminator( char cadena[] );


/**
 * @brief Capitaliza una palabra (ASCII).
 * @param cadena Palabra original.
 * @return Palabra capitalizada.
 */
char *capitaliza_palabra( const char cadena[] );

/**
 * @brief Convierte todos los caracteres de una cadena a minúsculas (ASCII).
 * @param cadena Cadena original.
 * @return Cadena en minúsculas.
 */
char *hace_minusculas_cadena( const char cadena[] );

#endif   // VALIDACION_H
