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
bool es_un_numero( const char cadena[] ) {
    if ( cadena == NULL || *cadena == '\0' ) return false;

    int i = 0;
    if ( cadena[ 0 ] == '-' || cadena[ 0 ] == '+' ) i++;

    for ( ; cadena[ i ] != '\0'; i++ ) {
        if ( !isdigit( (unsigned char) cadena[ i ] ) ) return false;
    }

    return i > ( cadena[ 0 ] == '-' || cadena[ 0 ] == '+' );
}

/**
 * @brief Convierte una cadena a número entero.
 *
 * @param cadena Cadena numérica válida.
 * @return Número entero resultante de la conversión.
 */
int convierte_a_numero( const char cadena[] ) {
    return atoi( cadena );   // Asume que es_un_numero ya fue usado
}

/**
 * @brief Verifica si una cadena tiene un formato de matrícula válido.
 *
 * Una matrícula válida tiene el formato 7 dígitos seguidos de una letra (e.g., 2141623a).
 *
 * @param cadena Cadena a validar.
 * @return true si cumple con el formato esperado, false en caso contrario.
 */
bool el_formato_de_matricula_es_valido( const char cadena[] ) {
    if ( cadena == NULL || strlen( cadena ) != 8 ) return false;

    for ( int i = 0; i < 7; i++ ) {
        if ( !isdigit( (unsigned char) cadena[ i ] ) ) return false;
    }

    if ( !isalpha( (unsigned char) cadena[ 7 ] ) ) return false;

    return true;
}

/**
 * @brief Valida que un nombre esté compuesto únicamente por letras y espacios.
 *
 * Usa una expresión regular: ^[a-zA-Z ]+$
 *
 * @param cadena Nombre a validar.
 * @return true si el formato es válido, false en caso contrario.
 */
bool el_formato_de_nombre_es_valido( const char cadena[] ) {
    if ( cadena == NULL ) return false;

    regex_t     regex;
    const char *patron = "^[a-zA-Z ]+$";

    if ( regcomp( &regex, patron, REG_EXTENDED | REG_NOSUB ) != 0 ) {
        return false;
    }

    int resultado = regexec( &regex, cadena, 0, NULL, 0 );
    regfree( &regex );

    return resultado == 0;
}

/**
 * @brief Elimina espacios en blanco al principio y final de una cadena.
 *
 * Utiliza obtiene_indice_del_primer_caracter_no_blank y
 * obtiene_indice_del_ultimo_caracter_no_blank para cortar la cadena.
 *
 * @param cadena Cadena original.
 * @return Nueva cadena sin espacios en los extremos (modifica la original).
 */
char *remueve_espacios_sobrantes_principio_y_final( char cadena[] ) {
    if ( cadena == NULL ) return NULL;

    int inicio = obtiene_indice_del_primer_caracter_no_blank( cadena );
    int fin    = obtiene_indice_del_ultimo_caracter_no_blank( cadena );

    if ( inicio == -1 || fin == -1 ) {
        cadena[ 0 ] = '\0';
        return cadena;
    }

    int j = 0;
    for ( int i = inicio; i <= fin; i++ ) {
        cadena[ j++ ] = cadena[ i ];
    }

    cadena[ j ] = '\0';
    return cadena;
}

/**
 * @brief Obtiene el índice del primer carácter no blanco de una cadena.
 *
 * @param cadena Cadena a analizar.
 * @return Índice del primer carácter válido, o -1 si no hay ninguno.
 */
int obtiene_indice_del_primer_caracter_no_blank( const char cadena[] ) {
    if ( cadena == NULL ) return -1;

    for ( int i = 0; cadena[ i ] != '\0'; i++ ) {
        if ( !isspace( (unsigned char) cadena[ i ] ) ) return i;
    }

    return -1;
}

/**
 * @brief Obtiene el índice del último carácter no blanco de una cadena.
 *
 * @param cadena Cadena a analizar.
 * @return Índice del último carácter válido, o -1 si no hay ninguno.
 */
int obtiene_indice_del_ultimo_caracter_no_blank( const char cadena[] ) {
    if ( cadena == NULL ) return -1;

    int len = strlen( cadena );
    for ( int i = len - 1; i >= 0; i-- ) {
        if ( !isspace( (unsigned char) cadena[ i ] ) ) return i;
    }

    return -1;
}

/**
 * @brief Llena toda la cadena con caracteres nulos ('\0').
 *
 * @param cadena Cadena que se va a limpiar.
 */
void rellena_cadena_con_null_terminator( char cadena[] ) {
    if ( cadena == NULL ) return;

    for ( int i = 0; cadena[ i ] != '\0'; i++ ) {
        cadena[ i ] = '\0';
    }
}

/**
 * @brief Convierte una cadena en minúsculas.
 *
 * @param cadena Cadena original.
 * @return Nueva cadena con todos los caracteres en minúsculas (debe ser liberada por el
 * usuario).
 */
char *hace_minusculas_cadena( const char cadena[] ) {
    if ( cadena == NULL ) return NULL;

    size_t len       = strlen( cadena );
    char  *resultado = malloc( len + 1 );
    if ( resultado == NULL ) return NULL;

    for ( size_t i = 0; i < len; i++ ) {
        resultado[ i ] = tolower( (unsigned char) cadena[ i ] );
    }

    resultado[ len ] = '\0';
    return resultado;
}

/**
 * @brief Capitaliza una palabra (primera letra en mayúscula, el resto en minúsculas).
 *
 * @param cadena Palabra a capitalizar.
 * @return Palabra capitalizada (debe ser liberada por el usuario).
 */
char *capitaliza_palabra( const char cadena[] ) {
    if ( cadena == NULL ) return NULL;

    size_t len = strlen( cadena );
    if ( len == 0 ) return strdup( "" );

    char *resultado = malloc( len + 1 );
    if ( resultado == NULL ) return NULL;

    resultado[ 0 ] = toupper( (unsigned char) cadena[ 0 ] );

    for ( size_t i = 1; i < len; i++ ) {
        resultado[ i ] = tolower( (unsigned char) cadena[ i ] );
    }

    resultado[ len ] = '\0';
    return resultado;
}

/**
 * @brief Capitaliza cada palabra de un nombre completo.
 *
 * Convierte la primera letra de cada palabra a mayúscula y el resto a minúscula.
 *
 * @param cadena Cadena con el nombre completo.
 * @return Nueva cadena capitalizada (debe ser liberada por el usuario).
 */
char *capitaliza_nombre_completo( const char cadena[] ) {
    if ( cadena == NULL ) return NULL;

    size_t len = strlen( cadena );
    if ( len == 0 ) return strdup( "" );

    char *resultado = malloc( len + 1 );
    if ( resultado == NULL ) return NULL;

    bool nueva_palabra = true;

    for ( size_t i = 0; i < len; i++ ) {
        if ( isspace( (unsigned char) cadena[ i ] ) ) {
            resultado[ i ] = cadena[ i ];
            nueva_palabra  = true;
        } else {
            if ( nueva_palabra ) {
                resultado[ i ] = toupper( (unsigned char) cadena[ i ] );
                nueva_palabra  = false;
            } else {
                resultado[ i ] = tolower( (unsigned char) cadena[ i ] );
            }
        }
    }

    resultado[ len ] = '\0';
    return resultado;
}