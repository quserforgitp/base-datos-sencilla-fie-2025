#ifndef REGISTRO_H
#define REGISTRO_H

#define MAX_BUFF_SIZE 100
typedef struct {
    long id_alumno;
    char nombre_alumno[MAX_BUFF_SIZE];
    char matricula_alumno[MAX_BUFF_SIZE];
} Registro;
#endif
