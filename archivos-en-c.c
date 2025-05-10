#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char id[ 100 ];
    char nombre[ 100 ];
    char matricula[ 100 ];
} Registro;

typedef struct {
    unsigned long numero_registros_actual;
    unsigned long ultimo_registro_mostrado;
    unsigned long capacidad;
    Registro     *registros;
} Registros;

typedef enum {
    UNA_SOLA_IMPRESION,
    HASTA_QUE_TERMINE,
    HASTA_QUE_EL_USUARIO_INDIQUE
} ModoImpresion;


void imprime_registros( Registros *rs, int numero_registros_a_imprimir,
                        ModoImpresion modo_impresion );

void imprime_registro( Registro *r );

Registros *carga_registros_de_db_en_memoria( FILE *archivo_db, int caracteres_por_linea,
                                             int capacidad_registros );

void imprime_info_estructura_registros( Registros *rs );

int main() {
    FILE *archivo = fopen( "archivo.db", "r" );
    if ( archivo == NULL ) {
        perror( "Error al abrir el archivo" );
        exit( 0 );
    }

    Registros *rs = carga_registros_de_db_en_memoria( archivo, 100, 1000 );

    imprime_info_estructura_registros( rs );

    printf( "Llamando a impresión UNA_SOLA_IMPRESION con 1 registro...\n" );
    imprime_registros( rs, 1, HASTA_QUE_EL_USUARIO_INDIQUE );
    imprime_registros( rs, 1, UNA_SOLA_IMPRESION );
    imprime_registros( rs, 1, HASTA_QUE_TERMINE );

    fclose( archivo );
}
void imprime_registros( Registros *rs, int numero_registros_a_imprimir,
                        ModoImpresion modo_impresion ) {
    switch ( modo_impresion ) {
        case UNA_SOLA_IMPRESION:
            printf( "[DEBUG] Entrando en: UNA_SOLA_IMPRESION\n" );
            int inicio = rs->ultimo_registro_mostrado;
            int fin    = inicio + numero_registros_a_imprimir;
            for ( int i = inicio; i < fin && i < rs->numero_registros_actual; i++ ) {
                imprime_registro( &( rs->registros[ i ] ) );
            }
            rs->ultimo_registro_mostrado = fin;
            break;

        case HASTA_QUE_EL_USUARIO_INDIQUE: {
            printf( "[DEBUG] Entrando en: HASTA_QUE_EL_USUARIO_INDIQUE\n" );
            char c                     = '\n';
            bool usuario_quiere_seguir = true;
            for ( int i = rs->ultimo_registro_mostrado;
                  i < rs->numero_registros_actual && usuario_quiere_seguir; i++ ) {
                imprime_registro( &( rs->registros[ i ] ) );
                rs->ultimo_registro_mostrado = i + 1;

                printf(
                    "Presione Enter para continuar, o 'n' y luego Enter para salir: " );

                c = getchar();
                if ( c != '\n' ) {
                    char aux;
                    while ( ( aux = getchar() ) != '\n' &&
                            aux != EOF );   // limpiar buffer
                }
                usuario_quiere_seguir = c != 'n' && c != 'N';
            }
            break;
        }

        case HASTA_QUE_TERMINE:
            printf( "[DEBUG] Entrando en: HASTA_QUE_TERMINE\n" );
            for ( int i = rs->ultimo_registro_mostrado; i < rs->numero_registros_actual;
                  i++ ) {
                imprime_registro( &( rs->registros[ i ] ) );
                rs->ultimo_registro_mostrado = i + 1;
            }
            break;

        default:
            printf( "[DEBUG] Entrando en: DEFAULT (modo no reconocido)\n" );
            break;
    }
}

void imprime_registro( Registro *r ) {
    printf(
        "Registro:\n"
        "  ID        -> %s\n"
        "  Nombre    -> %s\n"
        "  Matrícula -> %s\n",
        r->id, r->nombre, r->matricula );
}

void imprime_info_estructura_registros( Registros *rs ) {
    printf(
        "Registros:\n"
        "  Tiene        -> %ld registros\n"
        "  Capacidad    -> %ld registros\n",
        rs->numero_registros_actual, rs->capacidad );
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
    while ( fgets( linea, 100, archivo_db ) != NULL ) {
        linea[ strlen( linea ) - 1 ] = '\0';

        // convierto la linea a estructura de registros
        token = strtok( linea, "," );
        strncpy( r.id, token, 100 );

        token = strtok( NULL, "," );
        strncpy( r.nombre, token, 100 );

        token = strtok( NULL, "," );
        strncpy( r.matricula, token, 100 );

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