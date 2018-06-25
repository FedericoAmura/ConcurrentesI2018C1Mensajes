#ifndef CONCULANDIA_SERVIDOR_H
#define CONCULANDIA_SERVIDOR_H

#include <string>

#include "../Cola/Cola.h"
#include "../Cola/Mensajes.h"
#include "../Signal/SIGINT_Handler.h"

using namespace std;

class Servidor {
private:
    Cola<mensaje>* cola;
    SIGINT_Handler sigint_handler;

public:
    Servidor(const string& archivo, char letra);
    ~Servidor();

    void iniciar();
};


#endif //CONCULANDIA_SERVIDOR_H
