#include <iostream>
#include <unistd.h>

#include "Servidor.h"

#include "../GestorDB/Registro.h"
#include "../Signal/SignalHandler.h"

void Servidor::iniciar() {
    cout << "Iniciando en modo servidor" << endl;
    while(sigint_handler.getGracefulQuit() == 0) {
        this->procesarPeticion();
        cout << "Volvemos a esperar otra peticion" << endl;
    }
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
    response.mtype = request.pid;
    response.pid = getpid();
    // y ahora la procesamos segun lo que nos pidieron
    if (request.cmd == CMD_INSERTAR) {

        // aca insertamos un registro
        db->insertar(Registro(request.nombre, request.direccion, request.telefono));

        response.cmd = CMD_INSERTADO;
        strcpy(response.nombre,request.nombre);
        strcpy(response.direccion,request.direccion);
        strcpy(response.telefono,request.telefono);
        this->cola->escribir(response);
    } else if (request.cmd == CMD_CONSULTAR) {

        // aca consultamos registros
        vector<Registro> resultado = db->consulta(Registro(request.nombre, request.direccion, request.telefono));

        for (auto it : resultado) {
            response.cmd = CMD_RESPUESTA;
            strcpy(response.nombre, it.getNombre());
            strcpy(response.direccion, it.getDireccion());
            strcpy(response.telefono, it.getTelefono());
            this->cola->escribir(response);
        }

        // enviamos un ultimo registro para marcar el final
        response.cmd = CMD_VACIO;
        strcpy(response.nombre,"");
        strcpy(response.direccion,"");
        strcpy(response.telefono,"");
        this->cola->escribir(response);
    } else {
        // comando del request invalido
        response.cmd = CMD_ERROR;
        strcpy(response.nombre,"");
        strcpy(response.direccion,"");
        strcpy(response.telefono,"");
        this->cola->escribir(response);
    }

    return 0;
}

Servidor::Servidor(const string& archivo, const char letra, bool debug) : debug(debug) {
    cout << "SERVER - Creando servidor" << endl;
    SignalHandler::getInstance()->registrarHandler(SIGINT,&sigint_handler);
    this->cola = new Cola<mensaje>(archivo, letra);
    this->db = new GestorDB();
    cout << "SERVER - Servidor creado" << endl;
}

Servidor::~Servidor() {
    cout << "SERVER - Cerrando servidor" << endl;
    //this->cola->destruir();
    delete this->db;
    delete this->cola;
    cout << "SERVER - Servidor cerrado" << endl;
}