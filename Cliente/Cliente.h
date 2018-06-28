#ifndef CONCULANDIA_CLIENTE_H
#define CONCULANDIA_CLIENTE_H

#include <string>
#include <cstring>
#include <iostream>
#include <regex>
#include <unistd.h>
#include "../Util/Util.h"
#include "../Cola/Cola.h"
#include "../Cola/Mensajes.h"
#define OPCION_SALIR 1
#define OPCION_CONTINUAR 0

using namespace std;

class Cliente {
private:
    Cola<mensaje>* cola;
    bool debug;

    /**
     * Interpreta el comando ingresado para ejcutarlo.
     * @param comando String Comando tipeado por el usuario.
     * */
    int ejecutarComandos(string comando);

    /**
     * Inserta un registro en la tabla Personas.
     * @param cm Contiene los parametros obtenidos por la regular expresion
     * */
    int ejecutarInsertar(std::cmatch cm);

    /**
     * Lista los registros de la tabla personas que coincidan con los parametros.
     * @param cm Contiene los parametros obtenidos por la regular expresion
     * */
    int ejecutarListar(std::cmatch cm);

    /**
     * Lista todos los registros de la tabla personas.
     * */
    int ejecutarListarTodo();

    /**
     * Muestra el manual de comandos permitidos para el usuario
     * */
    int ejecutarAyuda();

    /**
     * Da la bienvenida al usuario
     * */
    void mostrarBienvenida();

public:
    Cliente(const string& archivo, char letra, bool debug);
    ~Cliente();

    /**
     * Inicia la terminal del cliente de base datos
     * */
    void iniciar();
};


#endif //CONCULANDIA_CLIENTE_H
