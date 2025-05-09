#include "utiles.h"

//
// =============================================================
//                     FUNCIONES GENERALES
// =============================================================
//

/**
 * @brief Muestra un mensaje con las instrucciones de uso del programa.
 */
void imprime_manual_de_uso() {
    printf(
        "Uso:\n"
        "\t./main <nombre_base_de_datos.db>\n"
        "(Note que el nombre del archivo es opcional)\n" );
}


//
// =============================================================
//                UTILIDADES PARA ENTRADA POR TECLADO
// =============================================================
//

//
// -------------------- Lectura de cadenas --------------------
//

/**
 * @brief Obtiene una entrada desde teclado y la retorna sin el salto de línea.
 *
 * Si la entrada supera el tamaño del búfer, se limpia el resto.
 * La memoria asignada debe liberarse con `free()` luego de su uso.
 *
 * @param tamanio_buffer_entrada Cantidad máxima de caracteres a leer.
 * @return Puntero a la cadena ingresada o NULL si ocurre un error.
 */
char *obtiene_entrada_por_teclado_sin_salto_linea( int tamanio_buffer_entrada ) {
    char *buffer_entrada = malloc( tamanio_buffer_entrada );

    if ( buffer_entrada == NULL ) {
        return NULL;
    }

    if ( fgets( buffer_entrada, tamanio_buffer_entrada, stdin ) == NULL ) {
        free( buffer_entrada );
        return NULL;
    }

    if ( existe_salto_de_linea_en_cadena( buffer_entrada ) ) {
        quita_salto_de_linea_de_cadena( buffer_entrada );
    } else {
        limpia_stdin();
    }

    return buffer_entrada;
}

//
// -------------------- Manejo del búfer de entrada --------------------
//

/**
 * @brief Elimina todos los caracteres restantes en stdin hasta encontrar un salto de
 * línea.
 */
void limpia_stdin() {
    int c;
    while ( ( c = getchar() ) != '\n' && c != EOF );
}

//
// -------------------- Manipulación de cadenas --------------------
//

/**
 * @brief Retorna true si la cadena contiene un salto de línea.
 *
 * @param cadena Cadena de texto a evaluar.
 * @return true si contiene '\n', false si no.
 */
bool existe_salto_de_linea_en_cadena( char cadena[] ) {
    return strchr( cadena, '\n' ) != NULL;
}

/**
 * @brief Reemplaza el primer salto de línea en la cadena por el carácter nulo '\0'.
 *
 * @param cadena Cadena que será modificada.
 */
void quita_salto_de_linea_de_cadena( char cadena[] ) {
    int indice_salto_linea       = strcspn( cadena, "\n" );
    cadena[ indice_salto_linea ] = '\0';
}