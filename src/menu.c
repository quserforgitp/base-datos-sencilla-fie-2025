#include "menu.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "archivo.h"
#include "errores.h"
#include "registro.h"
#include "utiles.h"
#include "validacion.h"

#define BUFF_SIZE 300

/**
 * @brief Muestra el menú de opciones y gestiona la interacción del usuario.
 *
 * Si el usuario elige la opción 1, se agrega una nueva entrada a la base de datos.
 * Se guarda el último ID en un archivo de índices para garantizar IDs únicos.
 *
 * @param nombre_del_archivo Nombre del archivo de base de datos. Si es NULL, se usa el
 * predeterminado.
 */
void muestra_menu( const char *nombre_del_archivo ) {
    // Determinar el nombre del archivo de base de datos y su archivo de id's
    bool        el_usuario_no_dio_nombre = nombre_del_archivo == NULL;
    const char *nombre_archivo_db =
        el_usuario_no_dio_nombre ? NOMBRE_PREDETERMINADO_ARCHIVO : nombre_del_archivo;

    // El archivo de id's tiene la misma base del nombre pero con extensión ".inf"
    char nombre_archivo_ids[ 100 ];
    sprintf( nombre_archivo_ids, "%s.inf", nombre_archivo_db );

    // Punteros a los archivos
    FILE *archivo_db;
    FILE *archivo_ids;

    // Buffer para capturar la entrada del usuario
    char *nuevo_nombre;

    // Variable para almacenar la opción seleccionada por el usuario
    int op = 0;

    // Ciclo principal del menú
    do {
        // Solicita al usuario que escoja una opcion del menu
        bool  no_es_un_numero = false;
        char *entrada_para_op;
        do {
            if ( no_es_un_numero ) {
                limpia_pantalla();
                fprintf( stderr, ">>> [ADVERT] '%s' no es un numero\n", entrada_para_op );
            }
            printf( "%s", MENU );
            entrada_para_op = obtiene_entrada_por_teclado_sin_salto_linea( BUFF_SIZE );
            no_es_un_numero = !es_un_numero( entrada_para_op );

        } while ( no_es_un_numero );
        limpia_pantalla();

        op = convierte_a_numero( entrada_para_op );
        switch ( op ) {
            case 1:
                puts( "============ AGREGAR UNA ENTRADA ===============" );

                // Abrir archivo de base de datos en modo "a" (append)
                archivo_db = fopen( nombre_archivo_db, "a" );

                // Si el archivo de id's no existe, crearlo e inicializarlo con 0
                if ( !existe_el_archivo( nombre_archivo_ids ) ) {
                    crea_el_archivo( nombre_archivo_ids );
                    inicializa_el_archivo_de_ids( nombre_archivo_ids );
                }

                // Abrir el archivo de id's en modo "r+" (lectura y escritura sin borrar
                // contenido)
                archivo_ids = fopen( nombre_archivo_ids, "r+" );

                // Verificar que los archivos se abrieron correctamente
                if ( no_se_pudo_abrir_archivo( archivo_db ) ) {
                    printf( "Error al abrir el archivo \"%s\"\n", nombre_archivo_db );
                    exit( ERR_ARCHIVO_NO_ABIERTO );
                }

                if ( no_se_pudo_abrir_archivo( archivo_ids ) ) {
                    printf( "Error al abrir el archivo \"%s\"\n", nombre_archivo_ids );
                    exit( ERR_ARCHIVO_NO_ABIERTO );
                }

                // Solicitar al usuario el nombre a agregar
                char *entrada_nuevo_nombre;
                bool  el_nombre_no_es_valido = false;
                do {
                    if ( el_nombre_no_es_valido ) {
                        limpia_pantalla();
                        fprintf( stderr,
                                 ">>> [ADVERT] El nombre -> [%s] no cumple con el "
                                 "formato valido.\n",
                                 entrada_nuevo_nombre );
                    }
                    printf( "Introduzca un nombre para agregar a la base de datos -> " );

                    entrada_nuevo_nombre = nuevo_nombre =
                        obtiene_entrada_por_teclado_sin_salto_linea( BUFF_SIZE );
                    nuevo_nombre = remueve_espacios_sobrantes_principio_y_final(
                        entrada_nuevo_nombre );

                    el_nombre_no_es_valido =
                        !el_formato_de_nombre_es_valido( nuevo_nombre );

                } while ( el_nombre_no_es_valido );
                limpia_pantalla();
                nuevo_nombre = capitaliza_nombre_completo( nuevo_nombre );

                // Solicitar al usuario la matricula a agregar
                char *entrada_matricula;
                char *nueva_matricula;
                bool  la_matricula_no_es_valida = false;
                do {
                    if ( la_matricula_no_es_valida ) {
                        limpia_pantalla();
                        fprintf( stderr,
                                 ">>> [ADVERT] La matricula -> [%s] es invalida.\n",
                                 nueva_matricula );
                    }
                    printf(
                        "Introduzca una matricula para agregar a la base de datos -> " );

                    entrada_matricula =
                        obtiene_entrada_por_teclado_sin_salto_linea( BUFF_SIZE );

                    nueva_matricula =
                        remueve_espacios_sobrantes_principio_y_final( entrada_matricula );
                    la_matricula_no_es_valida =
                        !el_formato_de_matricula_es_valido( nueva_matricula );

                } while ( la_matricula_no_es_valida );
                limpia_pantalla();

                // Estrucutra nuevo registro
                Registro nuevo_registro;


                // Asignar el nuevo nombre a la nueva estructura del nuevo registro
                strncpy( nuevo_registro.nombre_alumno, nuevo_nombre, 100 );

                // Asignar el la nueva matricula a la nueva estructura del nuevo registro
                strncpy( nuevo_registro.matricula_alumno, nueva_matricula, 100 );

                // Recuperar el último ID almacenado en el archivo de id's
                char string_id[ BUFF_SIZE + 1 ];
                fgets( string_id, sizeof( string_id ), archivo_ids );

                // Convertir el ID de cadena a número
                long indice_para_registro = atol( string_id );
                // Asignar el id para el nuevo registro a la estructura del nuevo registro
                indice_para_registro++;
                sprintf( string_id, "%ld", indice_para_registro );
                strncpy( nuevo_registro.id_alumno, string_id, 100 );
                // nuevo_registro.id_alumno = ++indice_para_registro;

                // Escribir la nueva entrada en la base de datos con el ID actualizado
                fprintf( archivo_db, "%s,%s,%s\n", nuevo_registro.id_alumno,
                         nuevo_registro.nombre_alumno, nuevo_registro.matricula_alumno );
                fflush( archivo_db );
                fclose( archivo_db );

                // Actualizar el ID en el archivo de id's
                fseek( archivo_ids, 0, SEEK_SET );
                fprintf( archivo_ids, "%s", nuevo_registro.id_alumno );
                fclose( archivo_ids );
                break;

            case 2:
                puts( "============ MOSTRAR REGISTROS ===============" );
                // Abrir archivo de base de datos en modo "r" (read)
                archivo_db = fopen( nombre_archivo_db, "r" );

                // Si el archivo de id's no existe, crearlo e inicializarlo con 0
                if ( !existe_el_archivo( nombre_archivo_ids ) ) {
                    crea_el_archivo( nombre_archivo_ids );
                    inicializa_el_archivo_de_ids( nombre_archivo_ids );
                }

                // Abrir el archivo de id's en modo "r" (lectura)
                archivo_ids = fopen( nombre_archivo_ids, "r" );

                // Verificar que los archivos se abrieron correctamente
                if ( no_se_pudo_abrir_archivo( archivo_db ) ) {
                    printf( "Error al abrir el archivo \"%s\"\n", nombre_archivo_db );
                    exit( ERR_ARCHIVO_NO_ABIERTO );
                }

                if ( no_se_pudo_abrir_archivo( archivo_ids ) ) {
                    printf( "Error al abrir el archivo \"%s\"\n", nombre_archivo_ids );
                    exit( ERR_ARCHIVO_NO_ABIERTO );
                }

                // cargar registros
                Registros *rs;
                rs = carga_registros_de_db_en_memoria( archivo_db, 100, 1000 );

                //  mecanismo para elegir opciones de impresion
                int opcion_impresion;
                do {
                    bool  no_es_numero = false;
                    char *entrada_para_opcion_impresion;
                    do {
                        if ( no_es_numero ) {
                            limpia_pantalla();
                            fprintf( stderr, ">>> [ADVERT] '%s' no es un numero\n",
                                     entrada_para_opcion_impresion );
                        }

                        printf(
                            "========== SELECCIONE UNA OPCION ==========\n"
                            "| 1.- Mostrar por tandas                  |\n"
                            "| 2.- Uno en uno hasta detenerlo          |\n"
                            "| 3.- Desde ultimo impreso hasta el final |\n"
                            "| 4.- Regesar al menu principal           |\n"
                            "===========================================\n"
                            "Seleccione una opcion -> " );
                        entrada_para_opcion_impresion =
                            obtiene_entrada_por_teclado_sin_salto_linea( BUFF_SIZE );

                        no_es_numero = !es_un_numero( entrada_para_opcion_impresion );

                    } while ( no_es_numero );
                    opcion_impresion =
                        convierte_a_numero( entrada_para_opcion_impresion );
                    limpia_pantalla();

                    printf( "Opcion elegida -> %d\n", opcion_impresion );
                    switch ( opcion_impresion ) {
                        case 1:
                            puts( "============ MOSTRANDO POR TANDAS ===============" );
                            bool  no_es_numero = false;
                            char *entrada_num_registros_por_tanda;
                            int   num_registros_por_tanda;
                            do {
                                if ( no_es_numero ) {
                                    limpia_pantalla();
                                    fprintf( stderr,
                                             ">>> [ADVERT] '%s' no es un numero\n",
                                             entrada_num_registros_por_tanda );
                                }

                                printf(
                                    "Cuantos registros quiere ver por impresion? -> " );
                                entrada_num_registros_por_tanda =
                                    obtiene_entrada_por_teclado_sin_salto_linea(
                                        BUFF_SIZE );

                                no_es_numero =
                                    !es_un_numero( entrada_num_registros_por_tanda );

                            } while ( no_es_numero );
                            limpia_pantalla();
                            num_registros_por_tanda =
                                convierte_a_numero( entrada_num_registros_por_tanda );
                            muestra_n_desde_el_actual( rs, num_registros_por_tanda );

                            // invocar funcion para mostrarlos por tandas
                            break;
                        case 2:
                            puts(
                                "============ MOSTRANDO UNO POR UNO HASTA DETENER "
                                "IMPRESION "
                                "===============" );

                            muestra_registros_hasta_que_usuario_decida_parar( rs );
                            break;
                        case 3:
                            puts(
                                "============ MOSTRANDO DESDE ULTIMO IMPRESO HASTA EL "
                                "FINAL"
                                "===============" );
                            muestra_registros_restantes( rs );
                            break;
                        case 4:
                            limpia_pantalla();
                            puts( ">>> [INFO] Volviendo al menu principal..." );
                            break;

                        default:
                            limpia_pantalla();
                            printf(
                                ">>> [ADVERT] La opción de impresion '%d' no es "
                                "válida.\n",
                                opcion_impresion );
                            break;
                    }
                } while ( opcion_impresion != 4 );

                // cerrar archivos
                fclose( archivo_db );
                fclose( archivo_ids );
                break;

            case 3:
                puts( "Saliendo del programa..." );
                break;

            default:
                limpia_pantalla();
                printf( ">>> [ADVERT] La opción '%d' no es válida.\n", op );
        }
    } while ( op != 3 );
}
