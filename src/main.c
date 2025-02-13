#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include <stdbool.h>

void imprime_manual_de_uso();

int main( int argc, char *argv[] )
{

    
    bool se_paso_mas_de_un_argumento_al_programa = argc > 2;
    bool se_paso_un_solo_argumento_al_programa = argc == 2;

    if (se_paso_mas_de_un_argumento_al_programa)
    {
        puts("numero de argumentos incorrecto");
        imprime_manual_de_uso();
        return 1;
    }

    const char *NOMBRE_ARCHIVO_RECIBIDO_POR_ARGUMENTO = (se_paso_un_solo_argumento_al_programa) ? argv[1] : NULL;
        

    muestra_menu(NOMBRE_ARCHIVO_RECIBIDO_POR_ARGUMENTO);
    
    return EXIT_SUCCESS;
}

void imprime_manual_de_uso() {
    printf("Uso:\n"\
           "\t./main <nombre_base_de_datos>\n"\
           "(note que el nombre del archivo es opcional)\n");
}
