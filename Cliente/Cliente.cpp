#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <regex>
#include "Cliente.h"

using namespace std;

void Cliente::iniciarTerminal() {
    cout << "Bienvenido al cliente de Base de Datos." << endl;
    cout << "Tipie 'ayuda' para conocer los comandos permitidos. Tipe 'exit' para salir." << endl;
    cout << endl;

    string comando;
    bool salir = false;
    while (!salir) {

        printf(">");
        getline(cin, comando, '\n');

        if (comando.compare("exit") == 0) {
            salir = true;
            cout<<"Adios"<<"!"<<endl;
        } else {
            this->ejecutarComandos(comando);
        }
    }
}

void Cliente::ejecutarComandos(string caracteristica) {

    std::regex e ("(insertar)\\((.*),(.*),(.*)\\)");

    std::cmatch cm;
    if (std::regex_match (caracteristica.c_str(),cm,e)) {

        mensaje request;
        mensaje response;

        request.mtype = REQUEST;
        request.pid = getpid();
        request.cmd = CMD_INSERTAR;
        strcpy(request.nombre,cm[2].str().c_str());
        strcpy(request.direccion,cm[3].str().c_str());
        strcpy(request.telefono,cm[4].str().c_str());

        this->cola->escribir(request);
        this->cola->leer(RESPONSE, &response);
        cout << "Registro insertado" << endl;

    } else if (caracteristica.compare("listar") == 0) {
        mensaje request;
        mensaje response;

        request.mtype = REQUEST;
        request.pid = getpid();
        request.cmd = CMD_CONSULTAR;
        this->cola->escribir(request);
        this->cola->leer(RESPONSE, &response);
        cout << "Consulta" << endl;

    } else if (caracteristica.compare("ayuda") == 0) {
        cout << endl;
        cout << "=============================================" << endl;
        cout << "                   AYUDA                     " << endl;
        cout << "=============================================" << endl;
        cout << "Comandos permitidos: " << endl;
        cout << endl;
        cout << "ayuda                                   Ayuda para el usuario." << endl;
        cout << "insertar(nombre,direccion, telefono)    Inserta un usuario." << endl;
        cout << "listar                                  Listar todos los usuarios insertados." << endl;
        cout << "exit                                    Salir." << endl;
        cout << endl;
    } else {
        cout<<"Comando no encontrado"<<"!"<<endl;
    }
}

void Cliente::iniciar() {

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


Cliente::Cliente(const string& archivo, const char letra, bool debug) : debug(debug) {
    cout << "CLIENT - Creando cliente" << endl;
    this->cola = new Cola<mensaje>(archivo, letra);
    cout << "CLIENT - Cliente creado" << endl;
}

Cliente::~Cliente() {
    cout << "CLIENT - Cerrando cliente" << endl;
    //this->cola->destruir();
    delete this->cola;
    cout << "CLIENT - Cliente cerrado" << endl;
}