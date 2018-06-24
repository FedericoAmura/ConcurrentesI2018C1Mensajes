#ifndef CONCULANDIA_UTIL_H
#define CONCULANDIA_UTIL_H

#include <string>
#include <algorithm>

using namespace std;

const int MODO_SERVIDOR = 1;
const int MODO_CLIENTE = 2;

typedef struct parametros {
    int modo;
} t_parametros;

class Util {

public:
    static t_parametros tomarParametros(int argc,char* argv[]);

    static string trim(const string& str);

    static bool esNumerico(const string& str);

    static int validarParametros(t_parametros parametros);

    static string obtenerMensajeError(int codigoMensaje);

    static string eliminarFinLinea(string cadena);

};


#endif //CONCULANDIA_UTIL_H
