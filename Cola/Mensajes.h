#ifndef MENSAJES_H_
#define MENSAJES_H_

#define	REQUEST 1
#define RESPONSE 2

#define CMD_INSERTAR 1
#define CMD_CONSULTAR 2
#define CMD_INSERTADO 3
#define CMD_RESPUESTA 4
#define CMD_VACIO 5

#define LEN_NOMBRE 61
#define LEN_DIRECCION 120
#define LEN_TELEFONO 13

typedef struct mensaje {
    long mtype;
    pid_t pid;
    int cmd;
    char nombre[LEN_NOMBRE];
    char direccion[LEN_DIRECCION];
    char telefono[LEN_TELEFONO];
} mensaje;

#endif /* MENSAJES_H_ */
