#include <stdio.h>
#include <stdlib.h>

#define MENU "\n" \
             "======= MENÚ ========\n" \
             "1. Agregar entrada   \n" \
             "2. <none>            \n" \
             "3. Salir             \n" \
             "=====================\n" \
             "Seleccione una opción -> "

void muestra_menu();

int main() {

    muestra_menu();
    
    return EXIT_SUCCESS;
}

void muestra_menu() {
    int op = 0;
    do
    {
        printf("%s", MENU);
        //leer la opcion que se selecciona
        scanf("%d", &op); getchar();// consumir el caracter \n que sobra
        // comprobar cual es el numero de opcion que se selecciono
        switch (op)
        {
            case 1:
                puts("Agregar una entrada");
                break;
            case 2:
                puts("<NONE>");
                break;
            case 3:
                puts("saliendo del programa");
                break;
            default:
                printf("la opcion '%d', no es una opcion valida!!!\n", op);
        }
    } while(op != 3);
}
