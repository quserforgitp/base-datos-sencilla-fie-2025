#include "menu.h"

void muestra_menu() {
    int op = 0;
    do {
        printf("%s", MENU);
        scanf("%d", &op); getchar(); // Consumir '\n'
        
        switch (op) {
            case 1:
                puts("Agregar una entrada");
                break;
            case 2:
                puts("<NONE>");
                break;
            case 3:
                puts("Saliendo del programa...");
                break;
            default:
                printf("La opción '%d' no es válida.\n", op);
        }
    } while(op != 3);
}

