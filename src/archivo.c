#include "archivo.h"

/**
 * Verifica si un archivo existe intentando abrirlo en modo lectura.
 */
bool existe_el_archivo( const char *nombre_archivo ) {
    return fopen( nombre_archivo, "r" ) != NULL;
}

/**
 * Intenta crear un archivo en modo "a" (append).
 * Si no puede crearlo, imprime un mensaje de error.
 */
bool crea_el_archivo( const char *nombre_archivo ) {
    if ( fopen( nombre_archivo, "a" ) == NULL ) {
        printf( "No pudo crearse el archivo \"%s\"\n", nombre_archivo );
        return false;
    }
    printf( "Se creó el archivo \"%s\"\n", nombre_archivo );
    return true;
}

/**
 * Retorna true si el puntero al archivo es NULL, lo que indica que no se pudo abrir.
 */
bool no_se_pudo_abrir_archivo( FILE *archivo ) {
    return archivo == NULL;
}

/**
 * Abre el archivo en modo "w" (escritura) para inicializarlo con el ID 0.
 * Si el archivo no se puede abrir, termina el programa con `exit(1)`.
 */
void inicializa_el_archivo_de_ids( const char *nombre_archivo ) {
    FILE *archivo_ids = fopen( nombre_archivo, "w" );

    if ( no_se_pudo_abrir_archivo( archivo_ids ) ) {
        printf( "No se pudo abrir el archivo \"%s\"\n", nombre_archivo );
        exit( 1 );
    }

    // Escribimos un 0 en el archivo como valor inicial de los IDs.
    fprintf( archivo_ids, "%d", 0 );
    fclose( archivo_ids );
}

Registros *carga_registros_de_db_en_memoria( FILE *archivo_db, int caracteres_por_linea,
                                             int capacidad_registros ) {
    char       linea[ caracteres_por_linea ];
    char      *token;
    Registro   r;
    Registros *rs = malloc( sizeof( Registros ) );

    if ( rs == NULL ) return NULL;

    rs->capacidad = capacidad_registros;
    rs->registros = malloc( sizeof( Registro ) * rs->capacidad );
    if ( rs->registros == NULL ) {
        free( rs );
        return NULL;
    }
    rs->numero_registros_actual = 0;
    while ( fgets( linea, caracteres_por_linea, archivo_db ) != NULL ) {
        linea[ strlen( linea ) - 1 ] = '\0';

        // convierto la linea a estructura de registros
        token = strtok( linea, "," );
        strncpy( r.id_alumno, token, caracteres_por_linea );

        token = strtok( NULL, "," );
        strncpy( r.nombre_alumno, token, caracteres_por_linea );

        token = strtok( NULL, "," );
        strncpy( r.matricula_alumno, token, caracteres_por_linea );

        // meter registro al arreglo de registros (cargar en memoria)
        if ( rs->numero_registros_actual < rs->capacidad ) {
            rs->registros[ rs->numero_registros_actual++ ] = r;
        } else {
            break;   // o return NULL;
        }
    }
    rs->ultimo_registro_mostrado = 0;
    return rs;
}

void imprime_registro( Registro *r ) {
    printf(
        "Registro:\n"
        "  ID        -> %s\n"
        "  Nombre    -> %s\n"
        "  Matrícula -> %s\n",
        r->id_alumno, r->nombre_alumno, r->matricula_alumno );
}

void imprime_info_estructura_registros( Registros *rs ) {
    printf(
        "Registros:\n"
        "  Tiene        -> %ld registros\n"
        "  Capacidad    -> %ld registros\n",
        rs->numero_registros_actual, rs->capacidad );
}

void limpia_buffer_de_entrada() {
    char aux;
    while ( ( aux = getchar() ) != '\n' && aux != EOF );   // limpiar buffer
}

char solicita_enter_o_n_para_continuar_o_salir() {
    printf( "---> Presione Enter para continuar, o 'n' y luego Enter para salir: " );

    char c = getchar();

    bool no_se_introdujo_solamente_enter;
    no_se_introdujo_solamente_enter = c != '\n';

    if ( no_se_introdujo_solamente_enter ) limpia_buffer_de_entrada();

    return c;
}

void muestra_registros_hasta_que_usuario_decida_parar( Registros *rs ) {
    bool no_se_pueden_mostrar_registros =
        !comprueba_condiciones_para_mostrar_registros( rs );
    if ( no_se_pueden_mostrar_registros ) return;

    bool      usuario_quiere_seguir = true;
    char      caracter_introducido;
    Registro *r_actual;

    int inicio           = rs->ultimo_registro_mostrado;
    int numero_registros = rs->numero_registros_actual;

    for ( int i = inicio; i < numero_registros && usuario_quiere_seguir; i++ ) {
        r_actual = &( rs->registros[ i ] );

        imprime_registro( r_actual );
        rs->ultimo_registro_mostrado = i + 1;

        if ( ( i + 1 ) == numero_registros ) {
            printf( ">>> [INFO]  Ya se han mostrado todos los registros...\n" );
            rs->ultimo_registro_mostrado = 0;

            printf(
                ">>> [INPUT] Desea reiniciar la impresion y continuar "
                "imprimiendo?...\n" );
            caracter_introducido = solicita_enter_o_n_para_continuar_o_salir();

            usuario_quiere_seguir =
                ( caracter_introducido != 'n' && caracter_introducido != 'N' );

            if ( usuario_quiere_seguir ) {
                i = -1;
            }
        } else {
            caracter_introducido = solicita_enter_o_n_para_continuar_o_salir();

            usuario_quiere_seguir =
                ( caracter_introducido != 'n' && caracter_introducido != 'N' );
        }
    }
}

void muestra_registros_restantes( Registros *rs ) {
    bool no_se_pueden_mostrar_registros =
        !comprueba_condiciones_para_mostrar_registros( rs );
    if ( no_se_pueden_mostrar_registros ) return;

    int       numero_registros = rs->numero_registros_actual;
    Registro *r_actual;
    for ( int i = rs->ultimo_registro_mostrado; i < numero_registros; i++ ) {
        r_actual = &( rs->registros[ i ] );

        imprime_registro( r_actual );

        rs->ultimo_registro_mostrado = i + 1;
        if ( ( i + 1 ) == numero_registros ) {
            printf( ">>> [INFO]  Ya se han mostrado todos los registros...\n" );
            rs->ultimo_registro_mostrado = 0;
        }
    }
}

void muestra_n_desde_el_actual( Registros *rs, int n ) {
    bool no_se_pueden_mostrar_registros =
        !comprueba_condiciones_para_mostrar_registros( rs );
    if ( no_se_pueden_mostrar_registros ) return;

    int inicio           = rs->ultimo_registro_mostrado;
    int numero_registros = rs->numero_registros_actual;

    int fin = inicio + n;

    bool n_excede_num_registros = ( inicio + n ) > numero_registros;
    int  numero_tandas_ajustado;
    if ( n_excede_num_registros ) {
        printf(
            ">>> [INFO] Se ajusto el numero de registros por tanda [%d] para mostrar "
            "porque\n"
            "           el numero recibido es mayor al numero de registros [%d]\n",
            n, numero_registros );

        numero_tandas_ajustado = ( numero_registros >= 100 ) ? 10 : numero_registros / 2;
        fin                    = numero_tandas_ajustado;
        printf( ">>> [INFO] Se imprimiran tandas de [%d]\n", numero_tandas_ajustado );
    }

    Registro *r_actual;

    char caracter_introducido;
    bool usuario_quiere_seguir               = true;
    bool se_han_mostrado_todos_los_registros = false;


    for ( int i = inicio; i < fin && usuario_quiere_seguir; i++ ) {
        r_actual = &( rs->registros[ i ] );
        imprime_registro( r_actual );

        if ( ( i + 1 ) == numero_registros ) {   // se imprimio el ultimo registro
            printf( ">>> [INFO]  Ya se han mostrado todos los registros...\n" );
            se_han_mostrado_todos_los_registros = true;
            printf( ">>> [INPUT] Desea reiniciar la impresion?...\n" );
            caracter_introducido = solicita_enter_o_n_para_continuar_o_salir();

            usuario_quiere_seguir =
                ( caracter_introducido != 'n' && caracter_introducido != 'N' );
            rs->ultimo_registro_mostrado = 0;
            if ( usuario_quiere_seguir ) {   // se reinicia la impresion
                i = -1;

                fin = n_excede_num_registros ? numero_tandas_ajustado : n;

                se_han_mostrado_todos_los_registros = false;
            }
        } else if ( i + 1 == fin ) {   // tanda de impresion completada
            printf( ">>> [INFO] Tanda de impresion completada!!!...\n" );
            printf( ">>> [INPUT] Desea seguir imprimiendo?...\n" );
            caracter_introducido = solicita_enter_o_n_para_continuar_o_salir();
            usuario_quiere_seguir =
                ( caracter_introducido != 'n' && caracter_introducido != 'N' );
            if ( usuario_quiere_seguir ) {
                fin += n;   // una tanda mas de impresion
            }
        }
    }

    if ( !se_han_mostrado_todos_los_registros ) {
        rs->ultimo_registro_mostrado = fin;
    }
}

bool tiene_registros_disponibles( const Registros *rs ) {
    return rs && ( rs->numero_registros_actual ) > 0;
}

bool no_se_ha_mostrado_el_ultimo_aun( const Registros *rs ) {
    int ultimo_mostrado = rs->ultimo_registro_mostrado;
    int ultimo_registro = rs->numero_registros_actual;

    return rs && ( ultimo_mostrado != ultimo_registro );   // rs nulo -> false
}

bool comprueba_condiciones_para_mostrar_registros( const Registros *rs ) {
    CondicionMostrarRegistros condiciones[] = {
        { .pasa_la_comprobacion = tiene_registros_disponibles,
          .nombre_comprobacion  = "tiene_registros_disponibles",
          .mensaje_condicion_incumplida =
              "No hay registros disponibles para mostrar." } };

    int numero_elementos = sizeof( condiciones ) / sizeof( condiciones[ 0 ] );
    CondicionMostrarRegistros *c_actual;
    bool                       no_paso_verificacion;
    for ( int i = 0; i < numero_elementos; i++ ) {
        c_actual             = &condiciones[ i ];
        no_paso_verificacion = !( c_actual->pasa_la_comprobacion( rs ) );

        if ( no_paso_verificacion ) {
            printf( ">>> [INFO]  %s\n", c_actual->mensaje_condicion_incumplida );
            return false;
        }
    }
    return true;
}