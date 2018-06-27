#ifndef MENSAJES_GESTORDB_H
#define MENSAJES_GESTORDB_H

#include "Registro.h"
#include <vector>

class GestorDB {
    public:
        std::vector<Registro> consulta(Registro request);
        void insertar(Registro r);
        ~GestorDB();
        GestorDB();

    private:
        std::vector<Registro> datos;

};


#endif //MENSAJES_GESTORDB_H
