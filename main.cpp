#include <iostream>

#include "Cliente/Cliente.h"
#include "Servidor/Servidor.h"
#include "Util/Util.h"

int main(int argc, char* argv[]) {
    static const string ARCHIVO = "/bin/ls";
    static const char LETRA = 'h';

    t_parametros params = Util::tomarParametros(argc, argv);
    int codigoValidacion = Util::validarParametros(params);
    if (codigoValidacion != 0) {
        cout << Util::obtenerMensajeError(codigoValidacion) << endl;
        return 1;
    }

    if (MODO_CLIENTE == params.modo) {
        Cliente cliente(ARCHIVO, LETRA, params.debug);
        cliente.iniciar();
    } else if (MODO_SERVIDOR == params.modo) {
        Servidor server(ARCHIVO, LETRA, params.debug);
        server.iniciar();
    }

    return 0;
}