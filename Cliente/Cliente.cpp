#include <iostream>
#include <unistd.h>

#include "Cliente.h"

using namespace std;

void Cliente::iniciar() {
    cout << "Iniciando en modo cliente" << endl;
    char input = 'a';
    while (input != '0') {
        cout << endl;
        cout << "------- MENU -------" << endl;
        cout << "0: Salir" << endl;
        cout << "1: Consultar personas" << endl;
        cout << "2: Alta de persona" << endl;
        cout << "Seleccione una opcion: ";
        cin >> input;

        switch (input) {
            case '0':
                cout << endl;
                cout << "Se procedera a cerrar el cliente" << endl;
                break;
            case '1': {
                consultarPersona();
                break;
            }
            case '2': {
                altaPersona();
                break;
            }
            default:
                cout << "Opcion no reconocida" << endl;
                break;
        }
    }
}

int Cliente::consultarPersona() {
    mensaje request;
    mensaje response;

    cout << endl;
    cout << "=============================================" << endl;
    cout << "             Consulta de personas            " << endl;
    cout << "=============================================" << endl;

    request.mtype = REQUEST;
    request.pid = getpid();
    request.cmd = CMD_CONSULTAR;
    strcpy(request.nombre,"Estamos");
    strcpy(request.direccion,"Consultando");
    strcpy(request.telefono,"Gente");

    cout << "Vamos a enviar la consulta" << endl;

    this->cola->escribir(request);

    cout << "Enviamos la consulta" << endl;

    this->cola->leer(RESPONSE, &response);

    cout << "Recibimos la respuesta" << endl;

    cout << "mtype " << response.mtype << endl;
    cout << "pid " << response.pid << endl;
    cout << "cmd " << response.cmd << endl;
    cout << "nombre " << response.nombre << endl;
    cout << "direccion " << response.direccion << endl;
    cout << "telefono " << response.telefono << endl;

    return 0;
}

int Cliente::altaPersona() {
    mensaje request;
    mensaje response;

    cout << endl;
    cout << "=============================================" << endl;
    cout << "               Alta de persona               " << endl;
    cout << "=============================================" << endl;

    request.mtype = REQUEST;
    request.pid = getpid();
    request.cmd = CMD_CONSULTAR;
    strcpy(request.nombre,"Damos");
    strcpy(request.direccion,"de alta");
    strcpy(request.telefono,"Personas");

    cout << "Vamos a enviar la consulta" << endl;

    this->cola->escribir(request);

    cout << "Enviamos la consulta" << endl;

    this->cola->leer(RESPONSE, &response);

    cout << "Recibimos la respuesta" << endl;

    cout << "mtype " << response.mtype << endl;
    cout << "pid " << response.pid << endl;
    cout << "cmd " << response.cmd << endl;
    cout << "nombre " << response.nombre << endl;
    cout << "direccion " << response.direccion << endl;
    cout << "telefono " << response.telefono << endl;

    return 0;
}

Cliente::Cliente(const string& archivo, const char letra) {
    cout << "Creando cliente" << endl;
    this->cola = new Cola<mensaje>(archivo, letra);
    cout << "Cliente creado" << endl;
}

Cliente::~Cliente() {
    delete this->cola;
}