#ifndef REGISTRO_H
#define REGISTRO_H

#define MAX_BUFF_SIZE 100
typedef struct {
    char id_alumno[ MAX_BUFF_SIZE ];
    char nombre_alumno[ MAX_BUFF_SIZE ];
    char matricula_alumno[ MAX_BUFF_SIZE ];
} Registro;

typedef struct {
    unsigned long numero_registros_actual;
    unsigned long ultimo_registro_mostrado;
    unsigned long capacidad;
    Registro     *registros;
} Registros;

typedef struct {
    bool ( *pasa_la_comprobacion )( const Registros *rs );
    char *nombre_comprobacion;
    char *mensaje_condicion_incumplida;
} CondicionMostrarRegistros;
#endif
