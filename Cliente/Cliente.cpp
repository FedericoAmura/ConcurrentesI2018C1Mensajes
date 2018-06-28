#include "Cliente.h"


using namespace std;

void Cliente::iniciar() {
    this->mostrarBienvenida();
    string comando;
    int status = OPCION_CONTINUAR;
    while (status == OPCION_CONTINUAR) {
        printf(">");
        getline(cin, comando, '\n');
        status = this->ejecutarComandos(Util::trim(comando));
    }
}

int Cliente::ejecutarComandos(string comando) {
    int status = OPCION_CONTINUAR;
    std::regex eInsertar("(insertar)\\((.*),(.*),(.*)\\)");
    std::regex eListar("(listar)\\((.*),(.*),(.*)\\)");

    std::cmatch cm;
    if (std::regex_match(comando.c_str(),cm,eInsertar)) {
        if (cm[2].str().size() > LEN_NOMBRE ||
                cm[3].str().size() > LEN_DIRECCION ||
                cm[4].str().size() > LEN_TELEFONO) {
            cout << "Campos muy largos" << endl;
            return OPCION_CONTINUAR;
        }
        status = this->ejecutarInsertar(cm);
    } else if (std::regex_match(comando.c_str(),cm,eListar)) {
        if (cm[2].str().size() > LEN_NOMBRE ||
            cm[3].str().size() > LEN_DIRECCION ||
            cm[4].str().size() > LEN_TELEFONO) {
            cout << "Campos muy largos" << endl;
            return OPCION_CONTINUAR;
        }
        status = this->ejecutarListar(cm);
    } else if (comando.compare("listar") == 0) {
        status = this->ejecutarListarTodo();
    } else if (comando.compare("ayuda") == 0) {
        status = this->ejecutarAyuda();
    } else if (comando.compare("salir") == 0) {
        cout << endl;
        cout << "Adios." << endl;
        status = OPCION_SALIR;
    } else {
        cout<<"Comando no encontrado"<<endl;
    }
    return status;
}


int Cliente::ejecutarInsertar(std::cmatch cm) {
    mensaje request;
    mensaje response;

    request.mtype = REQUEST;
    request.pid = getpid();
    request.cmd = CMD_INSERTAR;
    strcpy(request.nombre,cm[2].str().c_str());
    strcpy(request.direccion,cm[3].str().c_str());
    strcpy(request.telefono,cm[4].str().c_str());

    if (this->cola->escribir(request) == -1) return OPCION_SALIR;

    if (this->cola->leer(getpid(), &response) == -1) return OPCION_SALIR;

    if (response.cmd == CMD_INSERTADO) {
        cout << "Se inserto el registro" << endl;
        cout << "Nombre - Direccion - Telefono" << endl;
        cout << response.nombre << " - " << response. direccion << " - " << response.telefono << endl;
    } else {
        cout << "Error al insertar registro" << endl;
    }

    return OPCION_CONTINUAR;
}

int Cliente::ejecutarListar(std::cmatch cm) {
    mensaje request;
    mensaje response;

    request.mtype = REQUEST;
    request.pid = getpid();
    request.cmd = CMD_CONSULTAR;
    strcpy(request.nombre,cm[2].str().c_str());
    strcpy(request.direccion,cm[3].str().c_str());
    strcpy(request.telefono,cm[4].str().c_str());

    if (this->cola->escribir(request) == -1) return OPCION_SALIR;

    if (this->cola->leer(getpid(), &response) == -1) return OPCION_SALIR;
    if (response.cmd == CMD_VACIO) {
        cout << "Su consulta no encontro ningun registro" << endl;
    } else {
        cout << "Nombre - Direccion - Telefono" << endl;
        while (response.cmd != CMD_VACIO) {
            cout << response.nombre << " - " << response. direccion << " - " << response.telefono << endl;
            this->cola->leer(getpid(), &response);
        }
    }

    return OPCION_CONTINUAR;
}

int Cliente::ejecutarListarTodo() {
    mensaje request;
    mensaje response;

    request.mtype = REQUEST;
    request.pid = getpid();
    request.cmd = CMD_CONSULTAR;
    strcpy(request.nombre,"");
    strcpy(request.direccion,"");
    strcpy(request.telefono,"");

    if (this->cola->escribir(request) == -1) return OPCION_SALIR;

    if (this->cola->leer(getpid(), &response) == -1) return OPCION_SALIR;

    if (response.cmd == CMD_VACIO) {
        cout << "Su consulta no encontro ningun registro" << endl;
    } else {
        cout << "Nombre - Direccion - Telefono" << endl;
        while (response.cmd != CMD_VACIO) {
            cout << response.nombre << " - " << response. direccion << " - " << response.telefono << endl;
            this->cola->leer(getpid(), &response);
        }
    }

    return OPCION_CONTINUAR;
}

int Cliente::ejecutarAyuda() {
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

    return OPCION_CONTINUAR;
}

void Cliente::mostrarBienvenida() {
    cout << endl;
    cout << "Bienvenido al cliente de Base de Datos." << endl;
    cout << "Ingrese 'ayuda' para conocer los comandos permitidos." << endl;
    cout << endl;
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