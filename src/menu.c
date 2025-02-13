#include "menu.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_ARCHIVO_PREDETERMINADO "archivo.db"
#define BUFF_SIZE 300

bool existe_el_archivo(const char *nombre_archivo);
bool crea_el_archivo(const char *nombre_archivo);
bool no_se_pudo_abrir_archivo(FILE *archivo);
void inicializa_el_archivo_de_ids(const char *nombre_archivo);

void muestra_menu(const char *nombre_del_archivo) {

    // nombres de base de datos y archivo con el id
    bool el_usuario_no_dio_nombre = nombre_del_archivo == NULL;

    const char *nombre_archivo_db = el_usuario_no_dio_nombre ?
                                        NOMBRE_ARCHIVO_PREDETERMINADO : 
                                        nombre_del_archivo;

    char nombre_archivo_idx_actual[100];

    sprintf(nombre_archivo_idx_actual, "%s.inf", nombre_archivo_db);// el archivo id se llama igual pero con .inf al final
    
    // apuntadores a archivos 
    FILE *ptr_archivo_db;
    FILE *ptr_archivo_idx_actual;
    // buffer para capturar el texto que queremos mandar al archivo
    char nuevo_nombre[BUFF_SIZE + 1];
    
    // ciclo del menu para el usuario
    int op = 0;
    do {
        printf("%s", MENU);
        scanf("%d", &op); getchar(); // Consumir '\n'
        
        switch (op) 
        {
            case 1:
                puts("============AGREGAR UNA ENTRADA===============");

                ptr_archivo_db = fopen(nombre_archivo_db, "a");               
                // si no existe el del indice hay que crearlo y si ya existe hay que abrirlo en
                // r+ y posicionarlo al principio con fseek(ptr_archivo_idx_actual, 0, SEEK_SET); 
                if ( !existe_el_archivo(nombre_archivo_idx_actual) ) 
                {
                    crea_el_archivo(nombre_archivo_idx_actual);
                    // falta agregar el 0 al principio del archivo como id inicial
                    inicializa_el_archivo_de_ids(nombre_archivo_idx_actual);
                }
                // ahora si, abrelo en r+ para poder leer y escribir en el sin borrar el contenido anterior
                ptr_archivo_idx_actual = fopen(nombre_archivo_idx_actual, "r+");

                if ( no_se_pudo_abrir_archivo(ptr_archivo_db) )
                {
                    printf("Error al abrir el archivo \"%s\"\n", nombre_archivo_db);
                    exit(1);
                }
                
                if ( no_se_pudo_abrir_archivo(ptr_archivo_idx_actual) )
                {
                    printf("Error al abrir el archivo \"%s\"\n", nombre_archivo_idx_actual);
                    exit(1);
                }

                printf("Introduzca un nombre para agregar a la base de datos -> "); 
                
                fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
                
                // Removemos el salto de linea del fgets
                nuevo_nombre[strcspn(nuevo_nombre, "\n")] = 0;

                // Recuperar ID del archivo que guarda el ultimo
                char string_id[BUFF_SIZE + 1];

                fgets(string_id, sizeof(string_id), ptr_archivo_idx_actual);

                long indice_para_registro = atol(string_id);

                fprintf(ptr_archivo_db, "%ld,%s\n", ++indice_para_registro,  nuevo_nombre);
                fflush(ptr_archivo_db);
                fclose(ptr_archivo_db);
                
                // actualizar el indice en el archivo de indices
                fseek(ptr_archivo_idx_actual, 0, SEEK_SET);
                fprintf(ptr_archivo_idx_actual, "%ld", indice_para_registro);
                fclose(ptr_archivo_idx_actual);
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


bool existe_el_archivo(const char *nombre_archivo) {
    return fopen(nombre_archivo, "r") != NULL;
}
bool crea_el_archivo(const char *nombre_archivo) {

    if ( fopen(nombre_archivo, "a") == NULL )
    {
        printf("no pudo crearse el archivo \"%s\"\n", nombre_archivo);
        return false;
    } 
    printf("se creo el archivo  \"%s\"\n", nombre_archivo);
    return true;
}

bool no_se_pudo_abrir_archivo(FILE *archivo) {
    return archivo == NULL;
}

void inicializa_el_archivo_de_ids(const char *nombre_archivo) {
    // ya existe el archivo
    // lo tengo que abrir en modo w
    FILE *archivo_ids = fopen(nombre_archivo, "w");

    if ( no_se_pudo_abrir_archivo(archivo_ids) ) {
        printf("no se pudo abrir el archivo \"%s\"\n", nombre_archivo);
        exit(1);
    }
    fprintf(archivo_ids, "%d", 0);
    fclose(archivo_ids);
}

