#include "menu.h"
#include "errores.h"
#include "archivo.h"
#include <stdbool.h>
#include "registro.h"
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 300

/**
 * @brief Muestra el menú de opciones y gestiona la interacción del usuario.
 * 
 * Si el usuario elige la opción 1, se agrega una nueva entrada a la base de datos.
 * Se guarda el último ID en un archivo de índices para garantizar IDs únicos.
 * 
 * @param nombre_del_archivo Nombre del archivo de base de datos. Si es NULL, se usa el predeterminado.
 */
void muestra_menu(const char *nombre_del_archivo) {

    // Determinar el nombre del archivo de base de datos y su archivo de id's
    bool el_usuario_no_dio_nombre = nombre_del_archivo == NULL;
    const char *nombre_archivo_db = el_usuario_no_dio_nombre ?
                                        NOMBRE_PREDETERMINADO_ARCHIVO :
                                        nombre_del_archivo;
    
    // El archivo de id's tiene la misma base del nombre pero con extensión ".inf"
    char nombre_archivo_ids[100];
    sprintf(nombre_archivo_ids, "%s.inf", nombre_archivo_db);

    // Punteros a los archivos
    FILE *archivo_db;
    FILE *archivo_ids;

    // Buffer para capturar la entrada del usuario
    char nuevo_nombre[BUFF_SIZE + 1];

    // Variable para almacenar la opción seleccionada por el usuario
    int op = 0;

    // Ciclo principal del menú
    do {
        printf("%s", MENU);
        scanf("%d", &op); getchar(); // Consumir '\n' para evitar problemas en fgets

        switch (op)
        {
            case 1:
                puts("============ AGREGAR UNA ENTRADA ===============");

                // Abrir archivo de base de datos en modo "a" (append)
                archivo_db = fopen(nombre_archivo_db, "a");

                // Si el archivo de id's no existe, crearlo e inicializarlo con 0
                if (!existe_el_archivo(nombre_archivo_ids)) {
                    crea_el_archivo(nombre_archivo_ids);
                    inicializa_el_archivo_de_ids(nombre_archivo_ids);
                }

                // Abrir el archivo de id's en modo "r+" (lectura y escritura sin borrar contenido)
                archivo_ids = fopen(nombre_archivo_ids, "r+");

                // Verificar que los archivos se abrieron correctamente
                if (no_se_pudo_abrir_archivo(archivo_db)) {
                    printf("Error al abrir el archivo \"%s\"\n", nombre_archivo_db);
                    exit(ERR_ARCHIVO_NO_ABIERTO);
                }

                if (no_se_pudo_abrir_archivo(archivo_ids)) {
                    printf("Error al abrir el archivo \"%s\"\n", nombre_archivo_ids);
                    exit(ERR_ARCHIVO_NO_ABIERTO);
                }

                // Solicitar al usuario el nombre a agregar
                printf("Introduzca un nombre para agregar a la base de datos -> ");
                fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
                // Eliminar el salto de línea que fgets agrega al final
                nuevo_nombre[strcspn(nuevo_nombre, "\n")] = 0;

                // Solicitar al usuario la matricula a agregar
                char nueva_matricula[BUFF_SIZE + 1];
                printf("Introduzca una matricula para agregar a la base de datos -> ");
                fgets(nueva_matricula, BUFF_SIZE, stdin);
                // Eliminar el salto de línea que fgets agrega al final
                nueva_matricula[strcspn(nueva_matricula, "\n")] = 0;


                // Estrucutra nuevo registro
                Registro nuevo_registro;

                                
                // Asignar el nuevo nombre a la nueva estructura del nuevo registro
                strncpy(nuevo_registro.nombre_alumno, nuevo_nombre, 100);
                
                // Asignar el la nueva matricula a la nueva estructura del nuevo registro
                strncpy(nuevo_registro.matricula_alumno, nueva_matricula, 100);

                // Recuperar el último ID almacenado en el archivo de id's
                char string_id[BUFF_SIZE + 1];
                fgets(string_id, sizeof(string_id), archivo_ids);

                // Convertir el ID de cadena a número
                long indice_para_registro = atol(string_id);
                // Asignar el id para el nuevo registro a la estructura del nuevo registro
                nuevo_registro.id_alumno = ++indice_para_registro;

                // Escribir la nueva entrada en la base de datos con el ID actualizado
                fprintf(archivo_db, "%ld,%s,%s\n", nuevo_registro.id_alumno, nuevo_registro.nombre_alumno, nuevo_registro.matricula_alumno);
                fflush(archivo_db);
                fclose(archivo_db);

                // Actualizar el ID en el archivo de id's
                fseek(archivo_ids, 0, SEEK_SET);
                fprintf(archivo_ids, "%ld", nuevo_registro.id_alumno);
                fclose(archivo_ids);
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

