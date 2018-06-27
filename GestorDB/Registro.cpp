#include "Registro.h"
#include <cstring>

Registro::Registro(const char *nombre, const char *direccion, const char *telefono) {
    strcpy(this->nombre, nombre);
    strcpy(this->direccion, direccion);
    strcpy(this->telefono, telefono);
}

char *Registro::getNombre() {
    return this->nombre;
}

char *Registro::getDireccion() {
    return this->direccion;
}

char *Registro::getTelefono() {
    return this->telefono;
}

void Registro::setNombre(const char *nombre) {
    strcpy(this->nombre, nombre);
}

void Registro::setDireccion(const char *direccion) {
    strcpy(this->direccion, direccion);
}

void Registro::setTelefono(const char *telefono) {
    strcpy(this->telefono, telefono);
}

Registro::Registro() {
    strcpy(this->nombre, "");
    strcpy(this->direccion, "");
    strcpy(this->telefono, "");
}
