#include <iostream>
#include <unistd.h>

#include "Servidor.h"

#include "../Signal/SignalHandler.h"

void Servidor::iniciar() {
    cout << "Iniciando en modo servidor" << endl;
    while(sigint_handler.getGracefulQuit() == 0) {
        sleep(1);
        cout << "Estamos en un loop" << endl;
    }
}

Servidor::Servidor(const string& archivo, const char letra) {
    cout << "Creando servidor" << endl;
    SignalHandler::getInstance()->registrarHandler(SIGINT,&sigint_handler);
    this->cola = new Cola<mensaje>(archivo, letra);
    cout << "Servidor creado" << endl;
}

Servidor::~Servidor() {
    cout << "Cerrando servidor" << endl;
    delete this->cola;
    cout << "Servidor cerrado" << endl;
}