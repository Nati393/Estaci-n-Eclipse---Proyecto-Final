#ifndef JUEGO_H
#define JUEGO_H

#include "model/Jugador.h"
#include "model/Habitacion.h"
#include "view/InterfazConsola.h"
#include "view/Mensajes.h"
#include "SistemaGuardado.h"
#include <vector>
#include <map>

class Juego {
private:
    Jugador* jugador;
    std::vector<Habitacion*> habitaciones;
    Habitacion* habitacionActual;
    bool juegoActivo;

    void crearMapa();
    void procesarMovimiento(const std::string& direccion);
    void procesarUsoItem(const std::string& nombreItem);
    void procesarRecogerItem(const std::string& nombreItem);
    void mostrarAyuda();
    void iniciarCombate();

public:
    Juego();
    ~Juego();

    void inicializarJuego();
    void ejecutar();
    void procesarComando(const std::string& comando);
};

#endif