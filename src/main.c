#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "utiles.h"
#include "errores.h"
#include <stdbool.h>

/**
 * @brief Punto de entrada del programa.
 * 
 * Se valida la cantidad de argumentos y se llama a la función muestra_menu()
 * para iniciar la interacción con el usuario.
 * 
 * @param argc Número de argumentos pasados al programa.
 * @param argv Lista de argumentos pasados al programa.
 * 
 * @return EXIT_SUCCESS si la ejecución es correcta, EXIT_FAILURE en caso de error.
 */
int main(int argc, char *argv[]) {
    // Verificar la cantidad de argumentos pasados al programa
    bool se_paso_mas_de_un_argumento_al_programa = argc > 2;
    bool se_paso_un_solo_argumento_al_programa = argc == 2;

    if (se_paso_mas_de_un_argumento_al_programa) {
        puts("Número de argumentos incorrecto");
        imprime_manual_de_uso();
        return ERR_NUM_ARGUMENTOS_INVALIDO;
    }

    // Si se proporciona un argumento, se usa como nombre de archivo, de lo contrario es NULL
    const char *nombre_archivo = se_paso_un_solo_argumento_al_programa ? argv[1] : NULL;

    // Llamar a la función principal del menú
    muestra_menu(nombre_archivo);

    return EXIT_SUCCESS;
}

