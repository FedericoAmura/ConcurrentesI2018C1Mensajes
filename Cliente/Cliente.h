#ifndef CONCULANDIA_CLIENTE_H
#define CONCULANDIA_CLIENTE_H

#include <string>

#include "../Cola/Cola.h"
#include "../Cola/Mensajes.h"

using namespace std;

class Cliente {
private:
    Cola<mensaje>* cola;

public:
    Cliente(const string& archivo, char letra);
    ~Cliente();

    void iniciar();
};


#endif //CONCULANDIA_CLIENTE_H
