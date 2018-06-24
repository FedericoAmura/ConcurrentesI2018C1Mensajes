#include <iostream>
#include "Util/Util.h"

int main(int argc, char* argv[]) {

    t_parametros params = Util::tomarParametros(argc, argv);
    int codigoValidacion = Util::validarParametros(params);
    if (codigoValidacion != 0) {
        cout << Util::obtenerMensajeError(codigoValidacion) << endl;
        return 1;
    }

    if (MODO_CLIENTE == params.modo) {
        cout << "Iniciando en modo cliente" << endl;
    } else if (MODO_SERVIDOR == params.modo) {
        cout << "Iniciando en modo servidor" << endl;
    }

    return 0;
}