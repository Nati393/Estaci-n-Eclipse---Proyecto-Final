#ifndef SISTEMA_GUARDADO_H
#define SISTEMA_GUARDADO_H

#include <string>
#include <fstream>

class Jugador;
class Habitacion;

class SistemaGuardado {
public:
    static bool guardarPartida(const std::string& archivo, Jugador* jugador, Habitacion* habitacionActual);
    static bool cargarPartida(const std::string& archivo, Jugador*& jugador, Habitacion*& habitacionActual);

private:
    static void guardarJugador(std::ofstream& archivo, Jugador* jugador);
    static void cargarJugador(std::ifstream& archivo, Jugador*& jugador);
};

#endif