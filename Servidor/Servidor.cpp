#include <iostream>

#include "Servidor.h"

void Servidor::iniciar() {
    cout << "Iniciando en modo servidor" << endl;
}

Servidor::Servidor(const string& archivo, const char letra) {
    cout << "Creando servidor" << endl;
    this->cola = new Cola<mensaje>(archivo, letra);
    cout << "Servidor creado" << endl;
}

Servidor::~Servidor() {
    delete this->cola;
}