#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"

#define NOMBRE_PREDETERMINADO_ARCHIVO "nombres.db"

/**
 * @brief Verifica si un archivo existe.
 *
 * @param nombre_archivo Nombre del archivo a verificar.
 * @return true si el archivo existe, false si no.
 */
bool existe_el_archivo( const char *nombre_archivo );

/**
 * @brief Crea un archivo si no existe.
 *
 * @param nombre_archivo Nombre del archivo a crear.
 * @return true si el archivo se creó correctamente, false si hubo un error.
 */
bool crea_el_archivo( const char *nombre_archivo );

/**
 * @brief Verifica si un archivo no se pudo abrir.
 *
 * @param archivo Puntero al archivo.
 * @return true si el archivo no se pudo abrir, false si se abrió correctamente.
 */
bool no_se_pudo_abrir_archivo( FILE *archivo );

/**
 * @brief Inicializa un archivo de IDs, escribiendo un 0 en él.
 *
 * @param nombre_archivo Nombre del archivo donde se guardarán los IDs.
 */
void inicializa_el_archivo_de_ids( const char *nombre_archivo );

void imprime_registro( Registro *r );

Registros *carga_registros_de_db_en_memoria( FILE *archivo_db, int caracteres_por_linea,
                                             int capacidad_registros );

void limpia_buffer_de_entrada();

void imprime_info_estructura_registros( Registros *rs );

char solicita_enter_o_n_para_continuar_o_salir();

void muestra_registros_hasta_que_usuario_decida_parar( Registros *rs );

void muestra_registros_restantes( Registros *rs );

void muestra_n_desde_el_actual( Registros *rs, int n );

bool tiene_registros_disponibles( const Registros *rs );

bool comprueba_condiciones_para_mostrar_registros( const Registros *rs );

#endif   // ARCHIVO_H
