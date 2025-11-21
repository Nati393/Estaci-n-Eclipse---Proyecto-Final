#ifndef INTERFAZ_CONSOLA_H
#define INTERFAZ_CONSOLA_H

#include <string>

class InterfazConsola {
public:
    static void mostrarTitulo(const std::string& titulo);
    static void mostrarMensaje(const std::string& mensaje);
    static void mostrarError(const std::string& error);
    static void mostrarExito(const std::string& exito);
    static void limpiarPantalla();
    static void pausa();
    static std::string leerComando();
};

#endif