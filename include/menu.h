#ifndef MENU_H
#define MENU_H

#include <stdio.h>

/**
 * @brief Define el menú de opciones a mostrar al usuario.
 */
#define MENU                  \
    "\n"                      \
    "======= MENÚ ========\n" \
    "1. Agregar entrada   \n" \
    "2. <none>            \n" \
    "3. Salir             \n" \
    "=====================\n" \
    "Seleccione una opción -> "

/**
 * @brief Nombre predeterminado del archivo de base de datos.
 */
#define NOMBRE_PREDETERMINADO_ARCHIVO "nombres.db"

/**
 * @brief Muestra el menú interactivo para gestionar una base de datos de nombres.
 *
 * @param nombre_del_archivo Nombre del archivo de base de datos. Si es NULL, se usa el
 * nombre predeterminado.
 */
void muestra_menu( const char *nombre_del_archivo );

#endif   // MENU_H
