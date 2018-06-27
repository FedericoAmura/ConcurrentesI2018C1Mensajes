#ifndef MENSAJES_REGISTRO_H
#define MENSAJES_REGISTRO_H

#define LEN_NOMBRE 61
#define LEN_DIRECCION 120
#define LEN_TELEFONO 13

class Registro {
    public:
        Registro(const char* nombre, const char* direccion, const char* telefono);
        Registro();
        ~Registro() = default;
        char* getNombre();
        char* getDireccion();
        char* getTelefono();
        void setNombre(const char* nombre);
        void setDireccion(const char* direccion);
        void setTelefono(const char* telefono);
    private:
        char nombre[LEN_NOMBRE];
        char direccion[LEN_DIRECCION];
        char telefono[LEN_TELEFONO];
};


#endif //MENSAJES_REGISTRO_H
