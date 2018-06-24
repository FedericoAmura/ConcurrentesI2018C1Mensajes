#include <iostream>

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
                cout << endl;
                cout << "=============================================" << endl;
                cout << "             Consulta de personas            " << endl;
                cout << "=============================================" << endl;
                break;
            }
            case '2': {
                cout << endl;
                cout << "=============================================" << endl;
                cout << "               Alta de persona               " << endl;
                cout << "=============================================" << endl;
                break;
            }
            default:
                cout << "Opcion no reconocida" << endl;
                break;
        }
    }
}

Cliente::Cliente(const string& archivo, const char letra) {
    cout << "Creando cliente" << endl;
    this->cola = new Cola<mensaje>(archivo, letra);
    cout << "Cliente creado" << endl;
}

Cliente::~Cliente() {
    delete this->cola;
}