/**
 * @file validacion.c
 * @brief Funciones auxiliares para validación y transformación de cadenas y caracteres.
 */

#include "validacion.h"

/**
 * @brief Verifica si una cadena representa un número entero válido.
 *
 * @param cadena Cadena de caracteres a validar.
 * @return true si es un número válido, false en caso contrario.
 */
bool es_un_numero( const char cadena[] );

/**
 * @brief Convierte una cadena a número entero.
 *
 * @param cadena Cadena numérica válida.
 * @return Número entero resultante de la conversión.
 */
int convierte_a_numero( const char cadena[] );

/**
 * @brief Verifica si una cadena tiene un formato de matrícula válido.
 *
 * @param cadena Cadena a validar.
 * @return true si cumple con el formato esperado, false en caso contrario.
 */
bool el_formato_de_matricula_es_valido( const char cadena[] );

/**
 * @brief Valida que un nombre esté compuesto únicamente por letras y espacios.
 *
 * @param cadena Nombre a validar.
 * @return true si el formato es válido, false en caso contrario.
 */
bool el_formato_de_nombre_es_valido( const char cadena[] );

/**
 * @brief Elimina espacios en blanco al principio y final de una cadena.
 *
 * @param cadena Cadena original.
 * @return Nueva cadena sin espacios en los extremos.
 */
char *remueve_espacios_sobrantes_principio_y_final( char cadena[] );

/**
 * @brief Obtiene el índice del primer carácter no blanco de una cadena.
 *
 * @param cadena Cadena a analizar.
 * @return Índice del primer carácter válido, o -1 si no hay ninguno.
 */
int obtiene_indice_del_primer_caracter_no_blank( const char cadena[] );

/**
 * @brief Obtiene el índice del último carácter no blanco de una cadena.
 *
 * @param cadena Cadena a analizar.
 * @return Índice del último carácter válido, o -1 si no hay ninguno.
 */
int obtiene_indice_del_ultimo_caracter_no_blank( const char cadena[] );

/**
 * @brief Llena toda la cadena con caracteres nulos ('\0').
 *
 * @param cadena Cadena que se va a limpiar.
 */
void rellena_cadena_con_null_terminator( char cadena[] );

/**
 * @brief Convierte una cadena UTF-8 de caracteres anchos a minúsculas.
 *
 * @param cadena Cadena de entrada en `wchar_t`.
 * @return Nueva cadena en minúsculas.
 */
wchar_t *hace_minusculas_cadena_utf8( const wchar_t cadena[] );

/**
 * @brief Capitaliza una palabra en UTF-8 (primera letra en mayúscula).
 *
 * @param cadena Palabra en `wchar_t`.
 * @return Palabra capitalizada.
 */
wchar_t *capitaliza_palabra_utf8( const wchar_t cadena[] );

/**
 * @brief Capitaliza cada palabra de un nombre completo en UTF-8.
 *
 * @param cadena Cadena con el nombre completo.
 * @return Cadena capitalizada palabra por palabra.
 */
wchar_t *capitaliza_nombre_completo_utf8( const wchar_t cadena[] );

/**
 * @brief Convierte una cadena en minúsculas.
 *
 * @param cadena Cadena original.
 * @return Nueva cadena con todos los caracteres en minúsculas.
 */
char *hace_minusculas_cadena( const char cadena[] );

/**
 * @brief Capitaliza una palabra (primera letra en mayúscula, el resto en minúsculas).
 *
 * @param cadena Palabra a capitalizar.
 * @return Palabra capitalizada.
 */
char *capitaliza_palabra( const char cadena[] );
