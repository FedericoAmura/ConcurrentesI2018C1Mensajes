#include <cstdlib>
#include <getopt.h>

#include "./Util.h"

using namespace std;

t_parametros Util::tomarParametros(int argc,char* argv[]) {
    int c;
    bool pendingParams = true;
    t_parametros params;
    params.modo = 0;

    while (pendingParams)
    {
        static struct option long_options[] =
            {
                    {"servidor",  no_argument, nullptr, 's'},
                    {"cliente",  no_argument, nullptr, 'c'},
                    {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "sc",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {

            case 'c':
                params.modo = MODO_CLIENTE;
                break;
            case 's':
                params.modo = MODO_SERVIDOR;
                break;
            case '?':
                break;
            default:
                pendingParams = false;
        }
    }

    return params;
}

string Util::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)  {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool Util::esNumerico(const string& str){

    int len = str.length();
    for (int i = 0; i < len; i++) {
        if (int(str[i])<48 || int(str[i]) > 57) {
            return false;
        }
    }

    return true;
}

int Util::validarParametros(t_parametros parametros) {
    if ((parametros.modo != MODO_SERVIDOR) && (parametros.modo != MODO_CLIENTE)) {
        return 1;
    }
    return 0;
}

string Util::obtenerMensajeError(int codigoMensaje) {
    string mensaje;
    switch (codigoMensaje) {
        case 1:
            mensaje = "Parametros incorrectos: Agregue -c para iniciar en modo cliente o -s para iniciar en modo servidor.";
            break;
        default:
            break;
    }
    return mensaje;
}

string Util :: eliminarFinLinea(string cadena) {
    cadena.erase(std::remove(cadena.begin(), cadena.end(), '\n'), cadena.end());
    return cadena;
}