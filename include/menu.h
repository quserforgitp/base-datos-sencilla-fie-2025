#ifndef MENU_H
#define MENU_H

#include <stdio.h>

#define MENU "\n" \
             "======= MENÚ ========\n" \
             "1. Agregar entrada   \n" \
             "2. <none>            \n" \
             "3. Salir             \n" \
             "=====================\n" \
             "Seleccione una opción -> "
#define NOMBRE_PREDETERMINADO_ARCHIVO "nombres.db"

void muestra_menu(const char *nombre_del_archivo);

#endif // MENU_H

