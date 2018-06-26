#include <cstring>
#include <iostream>
#include <regex>
#include <unistd.h>

#include "Cliente.h"

using namespace std;

void Cliente::iniciar() {
    cout << endl;
    cout << "Bienvenido al cliente de Base de Datos." << endl;
    cout << "Ingrese 'ayuda' para conocer los comandos permitidos." << endl;
    cout << endl;

    string comando;
    bool salir = false;
    while (!salir) {

        printf(">");
        getline(cin, comando, '\n');

        if (comando.compare("salir") == 0) {
            salir = true;
            cout << endl;
            cout << "Adios." << endl;
        } else {
            this->ejecutarComandos(comando);
        }
    }
}

void Cliente::ejecutarComandos(string caracteristica) {
    std::regex eInsertar("(insertar)\\((.*),(.*),(.*)\\)");
    std::regex eListar("(listar)\\((.*),(.*),(.*)\\)");

    std::cmatch cm;
    if (std::regex_match(caracteristica.c_str(),cm,eInsertar)) {
        mensaje request;
        mensaje response;

        request.mtype = REQUEST;
        request.pid = getpid();
        request.cmd = CMD_INSERTAR;
        strcpy(request.nombre,cm[2].str().c_str());
        strcpy(request.direccion,cm[3].str().c_str());
        strcpy(request.telefono,cm[4].str().c_str());

        this->cola->escribir(request);
        this->cola->leer(getpid(), &response);
        if (response.cmd == CMD_INSERTADO) {
            cout << "Se inserto el registro" << endl;
            cout << "Nombre - Direccion - Telefono" << endl;
            cout << response.nombre << " - " << response. direccion << " - " << response.telefono << endl;
        } else {
            cout << "Error al insertar registro" << endl;
        }
    } else if (std::regex_match(caracteristica.c_str(),cm,eListar)) {
        mensaje request;
        mensaje response;

        request.mtype = REQUEST;
        request.pid = getpid();
        request.cmd = CMD_CONSULTAR;
        strcpy(request.nombre,cm[2].str().c_str());
        strcpy(request.direccion,cm[3].str().c_str());
        strcpy(request.telefono,cm[4].str().c_str());

        this->cola->escribir(request);

        this->cola->leer(getpid(), &response);
        if (response.cmd == CMD_VACIO) {
            cout << "Su consulta no encontro ningun registro" << endl;
        } else {
            cout << "Nombre - Direccion - Telefono" << endl;
            while (response.cmd != CMD_VACIO) {
                cout << response.nombre << " - " << response. direccion << " - " << response.telefono << endl;
                this->cola->leer(getpid(), &response);
            }
        }
    } else if (caracteristica.compare("listar") == 0) {
        mensaje request;
        mensaje response;

        request.mtype = REQUEST;
        request.pid = getpid();
        request.cmd = CMD_CONSULTAR;
        strcpy(request.nombre,"");
        strcpy(request.direccion,"");
        strcpy(request.telefono,"");

        this->cola->escribir(request);

        this->cola->leer(getpid(), &response);
        if (response.cmd == CMD_VACIO) {
            cout << "Su consulta no encontro ningun registro" << endl;
        } else {
            cout << "Nombre - Direccion - Telefono" << endl;
            while (response.cmd != CMD_VACIO) {
                cout << response.nombre << " - " << response. direccion << " - " << response.telefono << endl;
                this->cola->leer(getpid(), &response);
            }
        }
    } else if (caracteristica.compare("ayuda") == 0) {
        cout << endl;
        cout << "=============================================" << endl;
        cout << "                   AYUDA                     " << endl;
        cout << "=============================================" << endl;
        cout << "Comandos permitidos: " << endl;
        cout << endl;
        cout << "ayuda                                   Ayuda para el usuario." << endl;
        cout << "insertar(nombre,direccion,telefono)     Inserta un usuario. Se pueden ingresar vacios." << endl;
        cout << "                                        Se debe respetar la cantidad de parametros y el orden" << endl;
        cout << "listar(nombre,direccion,telefono)       Listar los usuarios que coinciden con los valores ingresados, ignorando los vacios." << endl;
        cout << "listar                                  Listar todos los usuarios insertados." << endl;
        cout << "salir                                   Salir del programa." << endl;
        cout << endl;
    } else {
        cout<<"Comando no encontrado"<<endl;
    }
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