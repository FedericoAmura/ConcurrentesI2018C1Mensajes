#include <iostream>
#include <unistd.h>

#include "Servidor.h"

#include "../Signal/SignalHandler.h"

void Servidor::iniciar() {
    cout << "Iniciando en modo servidor" << endl;
    while(sigint_handler.getGracefulQuit() == 0) {
        this->procesarPeticion();
        cout << "Volvemos a esperar otra peticion" << endl;
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

int Servidor::procesarPeticion () {
    mensaje request;
    mensaje response;

    cout << "Esperamos una peticion" << endl;
    // leemos la respuesta
    this->cola->leer(REQUEST, &(request));

    cout << "Leemos la peticion" << endl;

    cout << "mtype " << request.mtype << endl;
    cout << "pid " << request.pid << endl;
    cout << "cmd " << request.cmd << endl;
    cout << "nombre " << request.nombre << endl;
    cout << "direccion " << request.direccion << endl;
    cout << "telefono " << request.telefono << endl;

    // preparamos la respuesta con lo generico
    response.mtype = RESPONSE;
    response.pid = getpid();
    response.cmd = CMD_CONSULTAR;
    strcpy(response.nombre,"Procesamos");
    strcpy(response.direccion,"Un");
    strcpy(response.telefono,"Request");

    // procesamos la peticion mientras completamos la respuesta
    cout << "Vamos a responder" << endl;

    this->cola->escribir(response);

    return 0;
}