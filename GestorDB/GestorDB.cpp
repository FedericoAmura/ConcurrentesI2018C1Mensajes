#include "GestorDB.h"

#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ARCHIVO_DB "db.txt"

std::vector <Registro> GestorDB::consulta(Registro request) {
    std::vector<Registro> response;
    bool match;

    for (auto it : datos) {
        match = true;
        if (strlen(request.getNombre()) > 0) {
            if (strcmp(request.getNombre(), it.getNombre()) != 0)
                match =false;
        }
        if (strlen(request.getDireccion()) > 0 && match) {
            if (strcmp(request.getDireccion(), it.getDireccion()) != 0)
                match = false;
        }
        if (strlen(request.getTelefono()) > 0 && match) {
            if (strcmp(request.getTelefono(), it.getTelefono()) != 0)
                match = false;
        }
        if (match) {
            response.push_back(it);
        }
    }

    return response;
}

void GestorDB::insertar(Registro r) {
    std::cout << "Insertando registro " << r.getNombre() << " " << r.getDireccion() << " " << r.getTelefono() << std::endl;
    datos.push_back(r);
}

GestorDB::~GestorDB() {
    std::fstream archivo;
    archivo.open(ARCHIVO_DB, std::fstream::out);
    std::cout << "Guardando registros..." << std::endl;
    for (auto it : datos) {
        archivo <<  it.getNombre() << "," << it.getDireccion() << "," << it.getTelefono() << std::endl;
    }
    archivo.close();
}

GestorDB::GestorDB() {
    std::fstream archivo;
    std::string linea;
    std::string campo;
    Registro r;

    archivo.open(ARCHIVO_DB);

    while (getline(archivo, linea)) {
        std::istringstream temp(linea);
        getline(temp, campo, ',');
        r.setNombre(campo.c_str());
        getline(temp, campo, ',');
        r.setDireccion(campo.c_str());
        getline(temp, campo, ',');
        r.setTelefono(campo.c_str());
        datos.push_back(r);
    }

    archivo.close();

}
